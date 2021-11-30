// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageRenderer.h"
#include "AdaptiveImageRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveBase64Util.h"
#include "AdaptiveCardGetResourceStreamArgs.h"
#include <robuffer.h>

typedef ::AdaptiveCards::Rendering::Uwp::XamlBuilder XamlBuilder;

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveImageRenderer::AdaptiveImageRenderer(winrt::com_ptr<XamlBuilder> xamlBuilder) : m_xamlBuilder(xamlBuilder)
    {
    }

    rtxaml::UIElement AdaptiveImageRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                    rtrender::AdaptiveRenderContext const& renderContext,
                                                    rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            return m_xamlBuilder->BuildImage(cardElement, renderContext, renderArgs);
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}

namespace AdaptiveCards::Rendering::Uwp
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // IMPORTANT! Methods below here are actually XamlBuilder methods. They're defined here because they're only used
    // by the AdaptiveImageRenderer. They exist on XamlBuilder because it's the only place we have that can track
    // loading and lifetime for images.
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    rtxaml::UIElement XamlBuilder::BuildImage(rtom::IAdaptiveCardElement const& adaptiveCardElement,
                                              rtrender::AdaptiveRenderContext const& renderContext,
                                              rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        auto adaptiveImage = adaptiveCardElement.as<rtom::AdaptiveImage>();

        auto hostConfig = renderContext.HostConfig();
        auto url = adaptiveImage.Url();

        auto imageUrl = GetUrlFromString(hostConfig, url);

        if (imageUrl == nullptr)
        {
            // TODO: is this right?
            renderContext.AddWarning(rtom::WarningStatusCode::AssetLoadFailed, L"Image not found");
            return nullptr;
        }

        uint32_t pixelWidth = adaptiveImage.PixelWidth();
        uint32_t pixelHeight = adaptiveImage.PixelHeight();

        bool hasExplicitMeasurements = (pixelWidth || pixelHeight);
        bool isAspectRatioNeeded = (pixelWidth && pixelHeight);

        // Get the image's size and style
        rtom::ImageSize size = rtom::ImageSize::None;
        if (!hasExplicitMeasurements)
        {
            size = adaptiveImage.Size();
        }

        if (size == rtom::ImageSize::None && !hasExplicitMeasurements)
        {
            size = hostConfig.Image().ImageSize();
        }

        auto imageStyle = adaptiveImage.Style();
        auto resourceResolvers = renderContext.ResourceResolvers();
        auto backgroundColor = adaptiveImage.BackgroundColor();
        // TODO: we can just use adaptiveImage here?
        auto isVisible = adaptiveCardElement.IsVisible();

        rtxaml::FrameworkElement frameworkElement{nullptr};

        // TODO: Not sure why it's been done this way
        if (imageStyle == rtom::ImageStyle::Person)
        {
            rtxaml::Shapes::Ellipse ellipse{};
            rtxaml::Shapes::Ellipse backgroundEllipse{};

            rtxaml::Media::Stretch imageStretch =
                (isAspectRatioNeeded) ? rtxaml::Media::Stretch::Fill : rtxaml::Media::Stretch::UniformToFill;

            // bool mustHideElement{true};

            auto parentElement = renderArgs.ParentElement();

            auto ellipseAsShape = ellipse.as<rtxaml::Shapes::Shape>();
            auto backgrondEllipseAsShape = backgroundEllipse.as<rtxaml::Shapes::Shape>();

            // TODO: I don't see this mustHideElement being used for anything. Was it intended to be used when we can't set image so we collapse the visual?
            /* auto mustHideElement = */
            SetImageOnUIElement(imageUrl, ellipse, resourceResolvers, (size == rtom::ImageSize::Auto), parentElement, ellipseAsShape, isVisible, imageStretch);

            if (size == rtom::ImageSize::None || size == rtom::ImageSize::Stretch || size == rtom::ImageSize::Auto || hasExplicitMeasurements)
            {
                ellipse.Stretch(imageStretch);
                backgroundEllipse.Stretch(imageStretch);
            }
            else
            {
                // Set the stretch for the ellipse - this is different to the stretch used for the image brush
                // above. This will force the ellipse to conform to fit within the confines of its parent.
                ellipse.Stretch(rtxaml::Media::Stretch::UniformToFill);
                backgroundEllipse.Stretch(rtxaml::Media::Stretch::UniformToFill);
            }

            if (!backgroundColor.empty())
            {
                // Fill the background ellipse with solid color brush
                auto color = GetColorFromString(HStringToUTF8(backgroundColor));
                // TODO: would be good to refactor it in single function call.
                auto backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);

                // Create a grid to contain the background color ellipse and the image ellipse
                rtxaml::Controls::Grid imageGrid{};
                XamlHelpers::AppendXamlElementToPanel(backgroundEllipse, imageGrid);
                XamlHelpers::AppendXamlElementToPanel(ellipse, imageGrid);

                frameworkElement = imageGrid;
            }
            else
            {
                // TODO: I don't need to cast, do I?
                frameworkElement = ellipse;
            }
        }
        else
        {
            rtxaml::Controls::Image xamlImage{};

            if (!backgroundColor.empty())
            {
                // Create a surrounding border with solid color background to contain the image
                rtxaml::Controls::Border border{};
                auto color = GetColorFromString(HStringToUTF8(backgroundColor));
                auto backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                border.Background(backgroundColorBrush);

                border.Child(xamlImage);

                frameworkElement = border;
            }
            else
            {
                frameworkElement = xamlImage;
            }

            if (isAspectRatioNeeded)
            {
                xamlImage.Stretch(rtxaml::Media::Stretch::Fill);
            }

            auto parentElement = renderArgs.ParentElement();
            // TODO: I don't see this mustHideElement being used anywhere. Was it inteended to be used when image was
            // not set? so we don't waste lasyout space?
            /*bool mustHideElement =*/
            SetImageOnUIElement(imageUrl, xamlImage, resourceResolvers, (size == rtom::ImageSize::Auto), parentElement, frameworkElement, isVisible);
        }

        auto sizeOptions = hostConfig.ImageSizes();

        if (hasExplicitMeasurements)
        {
            if (pixelWidth)
            {
                if (imageStyle == rtom::ImageStyle::Person)
                {
                    frameworkElement.Width(pixelWidth);
                }
                else
                {
                    frameworkElement.MaxWidth(pixelWidth);
                }
            }

            if (pixelHeight)
            {
                if (imageStyle == rtom::ImageStyle::Person)
                {
                    frameworkElement.Height(pixelHeight);
                }
                else
                {
                    frameworkElement.MaxHeight(pixelHeight);
                }
            }
        }
        else
        {
            if (size == rtom::ImageSize::Small || size == rtom::ImageSize::Medium || size == rtom::ImageSize::Large)
            {
                uint32_t imageSize;
                switch (size)
                {
                case rtom::ImageSize::Small:
                {
                    imageSize = sizeOptions.Small();
                    break;
                }

                case rtom::ImageSize::Medium:
                {
                    imageSize = sizeOptions.Medium();
                    break;
                }

                case rtom::ImageSize::Large:
                {
                    imageSize = sizeOptions.Large();
                    break;
                }
                default:
                {
                    /*return E_UNEXPECTED;*/
                    // TODO: do we return nullptr here?
                    return nullptr;
                }
                }

                frameworkElement.MaxWidth(imageSize);

                // We don't want to set a max height on the person ellipse as ellipses do not understand preserving
                // aspect ratio when constrained on both axes.
                if (imageStyle != rtom::ImageStyle::Person)
                {
                    frameworkElement.MaxHeight(imageSize);
                }
            }
        }

        auto adaptiveHorizontalAlignmentReference = adaptiveImage.HorizontalAlignment();

        // If the image doesn't have horizontal alignment set, check the render context for a parent value
        if (adaptiveHorizontalAlignmentReference == nullptr)
        {
            adaptiveHorizontalAlignmentReference = renderContext.HorizontalContentAlignment();
        }

        auto adaptiveHorizontalAlignment = GetValueFromRef(adaptiveHorizontalAlignmentReference, rtom::HAlignment::Left);

        switch (adaptiveHorizontalAlignment)
        {
        case rtom::HAlignment::Left:
            frameworkElement.HorizontalAlignment(rtxaml::HorizontalAlignment::Left);
            break;
        case rtom::HAlignment::Right:
            frameworkElement.HorizontalAlignment(rtxaml::HorizontalAlignment::Right);
            break;
        case rtom::HAlignment::Center:
            frameworkElement.HorizontalAlignment(rtxaml::HorizontalAlignment::Center);
            break;
        }

        frameworkElement.VerticalAlignment(rtxaml::VerticalAlignment::Top);
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Image", frameworkElement);

        auto selectAction = adaptiveImage.SelectAction();

        winrt::hstring altText = adaptiveImage.AltText();

        rtxaml::Automation::AutomationProperties::SetName(frameworkElement, altText);

        return ActionHelpers::HandleSelectAction(
            adaptiveCardElement, selectAction, renderContext, frameworkElement, XamlHelpers::SupportsInteractivity(hostConfig), true);
    }

    template<typename T>
    void XamlBuilder::SetImageOnUIElement(winrt::Windows::Foundation::Uri const& imageUrl,
                                          T const& uiElement,
                                          rtrender::AdaptiveCardResourceResolvers const& resolvers,
                                          bool isAutoSize,
                                          winrt::Windows::Foundation::IInspectable const& parentElement,
                                          winrt::Windows::Foundation::IInspectable const& imageContainer,
                                          bool isVisible,
                                          winrt::Windows::UI::Xaml::Media::Stretch stretch)
    {
        // TODO: not sure how it's being used..
        bool mustHideElement = true;

        // Get the image url scheme
        // TODO: what if uri is nullptr? do we wanna fail?
        winrt::hstring schemeName = imageUrl.SchemeName();

        // Get the resolver for the image
        if (resolvers != nullptr)
        {
            auto resolver = resolvers.Get(schemeName);
            // If we have a resolver
            if (resolver != nullptr)
            {
                // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
                // the tracker to subscribe to the ImageLoaded/Failed events
                rtxaml::Media::Imaging::BitmapImage bitmapImage{};

                if (!m_enableXamlImageHandling && (m_listeners.size() != 0))
                {
                    this->m_imageLoadTracker->TrackBitmapImage(bitmapImage);
                }

                bitmapImage.CreateOptions(rtxaml::Media::Imaging::BitmapCreateOptions::None);

                // Create the arguments to pass to the resolver
                auto args =
                    winrt::make<winrt::AdaptiveCards::Rendering::Uwp::implementation::AdaptiveCardGetResourceStreamArgs>(imageUrl);

                // And call the resolver to get the image stream
                auto getResourceStreamOperation = resolver.GetResourceStreamAsync(args);

                getResourceStreamOperation.Completed(
                    [this, uiElement, bitmapImage, stretch, isAutoSize, parentElement, imageContainer, isVisible](
                        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IRandomAccessStream> const& operation,
                        winrt::Windows::Foundation::AsyncStatus status) -> void // TODO: should it be void?
                    {
                        if (status == winrt::Windows::Foundation::AsyncStatus::Completed)
                        {
                            auto randomAccessStream = operation.GetResults();
                            if (randomAccessStream != nullptr)
                            {
                                // TODO: gotta work on this m_imageLoadTracker
                                this->m_imageLoadTracker->MarkFailedLoadBitmapImage(bitmapImage);
                                return;
                            }
                            SetImageSource(uiElement, bitmapImage, stretch);

                            auto setSourceAction = bitmapImage.SetSourceAsync(randomAccessStream);

                            setSourceAction.Completed(
                                [this, uiElement, isAutoSize, parentElement, imageContainer, isVisible](
                                    winrt::Windows::Foundation::IAsyncAction const&, winrt::Windows::Foundation::AsyncStatus status)
                                {
                                    if (status == winrt::Windows::Foundation::AsyncStatus::Completed && isAutoSize)
                                    {
                                        SetAutoSize(uiElement, parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                                    }
                                });
                        }
                        else
                        {
                            this->m_imageLoadTracker->MarkFailedLoadBitmapImage(bitmapImage);
                        }
                    });
            }
        }

        if (schemeName == L"data")
        {
            // Decode base 64 string

            winrt::hstring dataPath = imageUrl.Path();

            std::string data = AdaptiveBase64Util::ExtractDataFromUri(HStringToUTF8(dataPath));
            std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);

            // TODO: is this correct way to create buffer?
            winrt::Windows::Storage::Streams::Buffer buffer{static_cast<uint32_t>(decodedData.size())};

            /*ComPtr<::Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
            THROW_IF_FAILED(buffer.As(&bufferByteAccess));*/

            // BYTE* dataInternal{};
            // bufferByteAccess->Buffer(&dataInternal);

            // TODO: is this correct? look above how it was done before
            memcpy_s(buffer.data(), decodedData.size(), decodedData.data(), decodedData.size());

            buffer.Length(static_cast<uint32_t>(decodedData.size()));

            rtxaml::Media::Imaging::BitmapImage bitmapImage{};
            bitmapImage.CreateOptions(rtxaml::Media::Imaging::BitmapCreateOptions::IgnoreImageCache);

            // TODO: Do I need to cast to output stream?
            winrt::Windows::Storage::Streams::InMemoryRandomAccessStream randomAccessStream{};
            auto bufferWriteOperation = randomAccessStream.WriteAsync(buffer);

            bufferWriteOperation.Completed(
                [this, bitmapImage, randomAccessStream, uiElement, isAutoSize, parentElement, imageContainer, isVisible](
                    winrt::Windows::Foundation::IAsyncOperationWithProgress<uint32_t, uint32_t> const& /*operation*/,
                    winrt::Windows::Foundation::AsyncStatus /*status*/) -> void // TODO: should it be void?)
                {
                    randomAccessStream.Seek(0);
                    SetImageSource(uiElement, bitmapImage);

                    auto setSourceAction = bitmapImage.SetSourceAsync(randomAccessStream);

                    setSourceAction.Completed(
                        [this, bitmapImage, uiElement, isAutoSize, parentElement, imageContainer, isVisible](
                            winrt::Windows::Foundation::IAsyncAction const& /*operation*/, winrt::Windows::Foundation::AsyncStatus status)
                        {
                            if (status == winrt::Windows::Foundation::AsyncStatus::Completed & isAutoSize)
                            {
                                SetAutoSize(bitmapImage, parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                            }
                        });
                });
            m_writeAsyncOperations.push_back(bufferWriteOperation);
            mustHideElement = false;
        }

        // Otherwise, no resolver...
        if ((m_enableXamlImageHandling) || (m_listeners.size() == 0))
        {
            // If we've been explicitly told to let Xaml handle the image loading, or there are
            // no listeners waiting on the image load callbacks, use Xaml to load the images
            rtxaml::Media::Imaging::BitmapImage bitmapImage{};
            bitmapImage.UriSource(imageUrl);

            SetImageSource(uiElement, bitmapImage, stretch);

            if (isAutoSize)
            {
                SetAutoSize(uiElement, parentElement, imageContainer, isVisible, true /* imageFiresOpenEvent */);
            }
        }
        else
        {
            PopulateImageFromUrlAsync(imageUrl, uiElement);
        }
    }

    template<typename T>
    void XamlBuilder::PopulateImageFromUrlAsync(winrt::Windows::Foundation::Uri const& imageUrl, T const& imageControl)
    {
        winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter httpBaseProtocolFilter{};
        httpBaseProtocolFilter.AllowUI(false);

        winrt::Windows::Web::Http::HttpClient httpClient{httpBaseProtocolFilter};

        // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
        // the tracker to subscribe to the ImageLoaded/Failed events
        rtxaml::Media::Imaging::BitmapImage bitmapImage{};
        this->m_imageLoadTracker->TrackBitmapImage(bitmapImage);
        bitmapImage.CreateOptions(rtxaml::Media::Imaging::BitmapCreateOptions::None);

        auto getStreamOperation = httpClient.GetInputStreamAsync(imageUrl);

        getStreamOperation.Completed(
            [this, bitmapImage, imageControl](
                winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Storage::Streams::IInputStream,
                                                                        winrt::Windows::Web::Http::HttpProgress> const& operation,
                winrt::Windows::Foundation::AsyncStatus status) -> void // TODO: should it be void?)))
            {
                if (status == winrt::Windows::Foundation::AsyncStatus::Completed)
                {
                    auto imageStream = operation.GetResults();
                    // TODO: not totally sure about all this stream stuf...
                    winrt::Windows::Storage::Streams::InMemoryRandomAccessStream randomAccessStream{};
                    auto copyStreamOperation =
                        winrt::Windows::Storage::Streams::RandomAccessStream::CopyAsync(imageStream, randomAccessStream);
                    m_copyStreamOperations.push_back(copyStreamOperation);

                    copyStreamOperation.Completed(
                        [this, bitmapImage, randomAccessStream, imageControl](
                            winrt::Windows::Foundation::IAsyncOperationWithProgress<uint64_t, uint64_t> const& /*operation*/,
                            winrt::Windows::Foundation::AsyncStatus /*status*/) { randomAccessStream.Seek(0); });
                }
            });
        m_getStreamOperations.push_back(getStreamOperation);
    }

    template<typename T>
    void XamlBuilder::SetImageSource(T const& destination, rtxaml::Media::ImageSource const& imageSource, rtxaml::Media::Stretch stretch /*stretch*/)
    {
        destination.Source(imageSource);
    };

    template<>
    void XamlBuilder::SetImageSource<rtxaml::Shapes::Ellipse>(rtxaml::Shapes::Ellipse const& destination,
                                                              rtxaml::Media::ImageSource const& imageSource,
                                                              rtxaml::Media::Stretch stretch)
    {
        rtxaml::Media::ImageBrush imageBrush{};
        imageBrush.ImageSource(imageSource);

        imageBrush.Stretch(stretch);
        destination.Fill(imageBrush);
    };

    template<>
    void XamlBuilder::SetAutoSize<rtxaml::Shapes::Ellipse>(rtxaml::Shapes::Ellipse const& destination,
                                                           winrt::Windows::Foundation::IInspectable const& parentElement,
                                                           winrt::Windows::Foundation::IInspectable const& imageContainer,
                                                           bool isVisible,
                                                           bool imageFiresOpenEvent)
    {
        // Check if the image source fits in the parent container, if so, set the framework element's size to match the original image.
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            auto ellipseAsShape = imageContainer.as<rtxaml::Shapes::Shape>();

            auto ellipseBrush = ellipseAsShape.Fill();

            auto brushAsImageBrush = ellipseBrush.as<rtxaml::Media::ImageBrush>();

            auto imageSource = brushAsImageBrush.ImageSource();
            auto imageSourceAsBitmap = imageSource.as<rtxaml::Media::Imaging::BitmapSource>();

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Ellipse while the image loads, so that resizing is not noticeable
                ellipseAsShape.Visibility(rtxaml::Visibility::Collapsed);

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                // TODO: what's the point of eventToken if we don';t save it ?
                // EventRegistrationToken eventToken;
                // ComPtr<IInspectable> localParentElement(parentElement);

                // Take a weak reference to the parent to avoid circular references (Parent->Ellipse->ImageBrush->Lambda->(Parent))
                /*WeakRef weakParent;
                THROW_IF_FAILED(localParentElement.AsWeak(&weakParent));*/

                auto weakParent = winrt::make_weak(parentElement);

                // TODO: do we need a revoker/token?
                brushAsImageBrush.ImageOpened(
                    [ellipseAsShape, weakParent, isVisible](winrt::Windows::Foundation::IInspectable const& sender,
                                                            rtxaml::RoutedEventArgs /*args*/) -> void
                    {
                        if (isVisible)
                        {
                            auto lambdaBrushAsImageBrush = sender.as<rtxaml::Media::ImageBrush>();

                            auto lambdaImageSource = lambdaBrushAsImageBrush.ImageSource();
                            auto lamdaImageSourceAsBitmap = lambdaImageSource.as<rtxaml::Media::Imaging::BitmapSource>();

                            auto lambdaParentElement = weakParent.get();
                            // TODO: no reason to convert ellipse to framework element, because  FE -> Shape - cast will
                            // be successfull if ellipseAsShape is not null
                            if (ellipseAsShape != nullptr && lambdaParentElement != nullptr)
                            {
                                rtxaml::FrameworkElement k{nullptr};
                                rtxaml::Media::Imaging::BitmapSource as{nullptr};

                                XamlHelpers::SetAutoImageSize(ellipseAsShape, lambdaParentElement, lamdaImageSourceAsBitmap, isVisible);
                            }
                        }
                    });
            }
            else
            {
                XamlHelpers::SetAutoImageSize(ellipseAsShape, parentElement, imageSourceAsBitmap, isVisible);
            }
        }
    }

    template<typename T>
    void XamlBuilder::SetAutoSize(T const& destination,
                                  winrt::Windows::Foundation::IInspectable const& parentElement,
                                  winrt::Windows::Foundation::IInspectable const&, /* imageContainer */
                                  bool isVisible,
                                  bool imageFiresOpenEvent)
    {
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            /*ComPtr<IImage> xamlImage(destination);*/
            // TODO: am I doing this right? or need to create new object and pass destination in constructor?
            auto xamlImage = destination.as<rtxaml::Controls::Image>();
            auto imageSource = xamlImage.Source();
            auto imageSourceAsBitmapSource = imageSource.as<rtxaml::Media::Imaging::BitmapSource>();

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Image control while the image loads, so that resizing is not noticeable
                xamlImage.Visibility(rtxaml::Visibility::Collapsed);

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent

                // TODO: is this needed to create weak ref? or we can create weak ref out of PARENT ELEMENT directly?
                /*ComPtr<IInspectable> localParentElement(parentElement);*/

                // Take weak references to the image and parent to avoid circular references between this lambda and
                // its parents (Parent->Image->Lambda->(Parent and Image))
                auto weakParent = winrt::make_weak(parentElement);

                auto weakImage = winrt::make_weak(xamlImage);

                xamlImage.ImageOpened(
                    [weakImage, weakParent, imageSourceAsBitmapSource, isVisible](winrt::Windows::Foundation::IInspectable const& /*sender*/,
                                                                                  rtxaml::RoutedEventArgs const&
                                                                                  /*args*/) -> void
                    {
                        // TODO: is this correct way to cast weak ref?
                        if (const auto lambdaImageAsFrameworkElement = weakImage.get())
                        {
                            if (const auto lambdaParentElement = weakParent.get())
                            {
                                XamlHelpers::SetAutoImageSize(lambdaImageAsFrameworkElement, lambdaParentElement, imageSourceAsBitmapSource, isVisible);
                            }
                        }
                    });
            }
            else
            {
                XamlHelpers::SetAutoImageSize(xamlImage, parentElement, imageSourceAsBitmapSource, isVisible);
            }
        }
    }
}
