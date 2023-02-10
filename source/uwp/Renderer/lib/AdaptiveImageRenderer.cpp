// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageRenderer.h"
#include "AdaptiveImageRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveBase64Util.h"
#include "AdaptiveCardGetResourceStreamArgs.h"
#include <robuffer.h>
#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveImageRenderer::AdaptiveImageRenderer(winrt::com_ptr<render_xaml::XamlBuilder> xamlBuilder) :
        m_xamlBuilder(xamlBuilder)
    {
    }

    winrt::UIElement AdaptiveImageRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            return m_xamlBuilder->BuildImage(cardElement, renderContext, renderArgs);
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
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

    winrt::UIElement render_xaml::XamlBuilder::BuildImage(winrt::IAdaptiveCardElement const& adaptiveCardElement,
                                                          winrt::AdaptiveRenderContext const& renderContext,
                                                          winrt::AdaptiveRenderArgs const& renderArgs)
    {
        auto adaptiveImage = adaptiveCardElement.as<winrt::AdaptiveImage>();

        auto hostConfig = renderContext.HostConfig();
        auto url = adaptiveImage.Url();

        auto imageUrl = GetUrlFromString(hostConfig, url);

        if (imageUrl == nullptr)
        {
            renderContext.AddWarning(winrt::WarningStatusCode::AssetLoadFailed, L"Image not found");
            return nullptr;
        }

        auto isImageSvg = IsSvgImage(HStringToUTF8(url));

        uint32_t pixelWidth = adaptiveImage.PixelWidth();
        uint32_t pixelHeight = adaptiveImage.PixelHeight();

        bool hasExplicitMeasurements = (pixelWidth || pixelHeight);
        bool isAspectRatioNeeded = (pixelWidth && pixelHeight);

        // Get the image's size and style
        winrt::ImageSize size = winrt::ImageSize::None;
        if (!hasExplicitMeasurements)
        {
            size = adaptiveImage.Size();
        }

        if (size == winrt::ImageSize::None && !hasExplicitMeasurements)
        {
            size = hostConfig.Image().ImageSize();
        }

        auto imageStyle = adaptiveImage.Style();
        auto resourceResolvers = renderContext.ResourceResolvers();
        auto backgroundColor = adaptiveImage.BackgroundColor();
        auto isVisible = adaptiveCardElement.IsVisible();

        winrt::FrameworkElement frameworkElement{nullptr};
        winrt::ImageSource imageSource{nullptr};

        // Issue #8125
        if (imageStyle == winrt::ImageStyle::Person)
        {
            winrt::Ellipse ellipse{};
            winrt::Ellipse backgroundEllipse{};

            winrt::Stretch imageStretch = (isAspectRatioNeeded) ? winrt::Stretch::Fill : winrt::Stretch::UniformToFill;

            auto parentElement = renderArgs.ParentElement();

            auto ellipseAsShape = ellipse.as<winrt::Shape>();
            auto backgrondEllipseAsShape = backgroundEllipse.as<winrt::Shape>();

            imageSource = SetImageOnUIElement(imageUrl, ellipse, resourceResolvers, (size == winrt::ImageSize::Auto), parentElement, ellipseAsShape, isVisible, isImageSvg, imageStretch);

            if (size == winrt::ImageSize::None || size == winrt::ImageSize::Stretch || size == winrt::ImageSize::Auto || hasExplicitMeasurements)
            {
                ellipse.Stretch(imageStretch);
                backgroundEllipse.Stretch(imageStretch);
            }
            else
            {
                // Set the stretch for the ellipse - this is different to the stretch used for the image brush
                // above. This will force the ellipse to conform to fit within the confines of its parent.
                ellipse.Stretch(winrt::Stretch::UniformToFill);
                backgroundEllipse.Stretch(winrt::Stretch::UniformToFill);
            }

            if (!backgroundColor.empty())
            {
                // Fill the background ellipse with solid color brush
                auto color = GetColorFromString(HStringToUTF8(backgroundColor));
                backgroundEllipse.Fill(winrt::SolidColorBrush{color});

                // Create a grid to contain the background color ellipse and the image ellipse
                winrt::Grid imageGrid{};
                XamlHelpers::AppendXamlElementToPanel(backgroundEllipse, imageGrid);
                XamlHelpers::AppendXamlElementToPanel(ellipse, imageGrid);

                frameworkElement = imageGrid;
            }
            else
            {
                frameworkElement = ellipse;
            }
        }
        else
        {
            winrt::Image xamlImage{};

            if (!backgroundColor.empty())
            {
                // Create a surrounding border with solid color background to contain the image
                winrt::Border border{};
                auto color = GetColorFromString(HStringToUTF8(backgroundColor));
                border.Background(winrt::SolidColorBrush{color});

                border.Child(xamlImage);

                frameworkElement = border;
            }
            else
            {
                frameworkElement = xamlImage;
            }

            if (isAspectRatioNeeded)
            {
                xamlImage.Stretch(winrt::Stretch::Fill);
            }

            auto parentElement = renderArgs.ParentElement();

            imageSource = SetImageOnUIElement(imageUrl, xamlImage, resourceResolvers, (size == winrt::ImageSize::Auto), parentElement, frameworkElement, isVisible, isImageSvg);
        }

        auto sizeOptions = hostConfig.ImageSizes();

        if (hasExplicitMeasurements)
        {
            if (pixelWidth)
            {
                SetRasterizedPixelWidth(imageSource, pixelWidth);
                if (imageStyle == winrt::ImageStyle::Person)
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
                SetRasterizedPixelHeight(imageSource, pixelHeight);
                if (imageStyle == winrt::ImageStyle::Person)
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
            if (size == winrt::ImageSize::Small || size == winrt::ImageSize::Medium || size == winrt::ImageSize::Large)
            {
                uint32_t imageSize;
                switch (size)
                {
                case winrt::ImageSize::Small:
                {
                    imageSize = sizeOptions.Small();
                    break;
                }

                case winrt::ImageSize::Medium:
                {
                    imageSize = sizeOptions.Medium();
                    break;
                }

                case winrt::ImageSize::Large:
                {
                    imageSize = sizeOptions.Large();
                    break;
                }
                default:
                {
                    throw winrt::hresult_error(E_UNEXPECTED);
                }
                }

                frameworkElement.MaxWidth(imageSize);
                SetRasterizedPixelWidth(imageSource, imageSize);

                // We don't want to set a max height on the person ellipse as ellipses do not understand preserving
                // aspect ratio when constrained on both axes.
                if (imageStyle != winrt::ImageStyle::Person)
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

        auto adaptiveHorizontalAlignment = GetValueFromRef(adaptiveHorizontalAlignmentReference, winrt::HAlignment::Left);

        switch (adaptiveHorizontalAlignment)
        {
        case winrt::HAlignment::Left:
            frameworkElement.HorizontalAlignment(winrt::HorizontalAlignment::Left);
            break;
        case winrt::HAlignment::Right:
            frameworkElement.HorizontalAlignment(winrt::HorizontalAlignment::Right);
            break;
        case winrt::HAlignment::Center:
            frameworkElement.HorizontalAlignment(winrt::HorizontalAlignment::Center);
            break;
        }

        frameworkElement.VerticalAlignment(winrt::VerticalAlignment::Top);
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Image", frameworkElement);

        auto selectAction = adaptiveImage.SelectAction();

        winrt::hstring altText = adaptiveImage.AltText();

        winrt::AutomationProperties::SetName(frameworkElement, altText);

        return ActionHelpers::HandleSelectAction(
            adaptiveCardElement, selectAction, renderContext, frameworkElement, XamlHelpers::SupportsInteractivity(hostConfig), true);
    }

    template<typename T>
    winrt::ImageSource render_xaml::XamlBuilder::SetImageOnUIElement(winrt::Uri const& imageUrl,
                                                                     T const& uiElement,
                                                                     winrt::AdaptiveCardResourceResolvers const& resolvers,
                                                                     bool isAutoSize,
                                                                     winrt::IInspectable const& parentElement,
                                                                     winrt::IInspectable const& imageContainer,
                                                                     bool isVisible,
                                                                     bool isImageSvg,
                                                                     winrt::Stretch stretch)
    {
        bool mustHideElement = true;

        // Get the image url scheme
        winrt::hstring schemeName = imageUrl.SchemeName();

        // Get the resolver for the image
        if (resolvers)
        {
            auto resolver = resolvers.Get(schemeName);
            // If we have a resolver
            if (resolver)
            {
                // Create a Image to hold the image data.  We use BitmapImage & SvgImageSource in order to allow
                // the tracker to subscribe to the ImageLoaded/Failed events
                auto image = CreateImageSource(isImageSvg);

                if (!m_enableXamlImageHandling && (m_listeners.size() != 0))
                {
                    if (!isImageSvg)
                    {
                        image.as<winrt::BitmapImage>().CreateOptions(winrt::BitmapCreateOptions::None);
                    }
                    this->m_imageLoadTracker->TrackImage(image);
                }

                // Create the arguments to pass to the resolver
                auto args = winrt::make<winrt::implementation::AdaptiveCardGetResourceStreamArgs>(imageUrl);

                // And call the resolver to get the image stream
                auto getResourceStreamOperation = resolver.GetResourceStreamAsync(args);

                getResourceStreamOperation.Completed(
                    [this, weakThis = this->get_weak(), uiElement, image, stretch, isAutoSize, parentElement, imageContainer, isVisible, isImageSvg](
                        auto const& operation, auto status) -> void
                    {
                        if (status == winrt::AsyncStatus::Completed)
                        {
                            if (auto strongThis = weakThis.get())
                            {
                                auto randomAccessStream = operation.GetResults();
                                if (!randomAccessStream)
                                {
                                    this->m_imageLoadTracker->MarkFailedLoadImage(image);
                                    return;
                                }
                                strongThis->HandleAccessStreamForImageSource(uiElement, isAutoSize, parentElement, imageContainer, isVisible, isImageSvg, randomAccessStream, image, stretch);
                            }
                        }
                        else
                        {
                            if (auto strongThis = weakThis.get())
                            {
                                // Question: should we only mark as a failed image if (!m_enableXamlImageHandling && (m_listeners.size() != 0))
                                this->m_imageLoadTracker->MarkFailedLoadImage(image);
                            }
                        }
                    });
                return image;
            }
        }

        if (schemeName == L"data")
        {
            // Decode base 64 string
            winrt::hstring dataPath = imageUrl.Path();
            std::string data = AdaptiveBase64Util::ExtractDataFromUri(HStringToUTF8(dataPath));
            std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);

            winrt::DataWriter dataWriter{winrt::InMemoryRandomAccessStream{}};

            dataWriter.WriteBytes(std::vector<byte>{decodedData.begin(), decodedData.end()});

            auto image = CreateImageSource(isImageSvg);

            if (!isImageSvg)
            {
                image.as<winrt::BitmapImage>().CreateOptions(winrt::BitmapCreateOptions::IgnoreImageCache);
            }
            m_imageLoadTracker->TrackImage(image);

            auto streamWriteOperation = dataWriter.StoreAsync();

            streamWriteOperation.Completed(
                [weakThis = this->get_weak(), dataWriter, image, uiElement, isAutoSize, parentElement, imageContainer, isVisible, isImageSvg, stretch](
                    auto const& /*operation*/, auto /*status*/) -> void
                {
                    if (auto strongThis = weakThis.get())
                    {
                        if (const auto stream = dataWriter.DetachStream().try_as<winrt::InMemoryRandomAccessStream>())
                        {
                            stream.Seek(0);
                            strongThis->HandleAccessStreamForImageSource(uiElement, isAutoSize, parentElement, imageContainer, isVisible, isImageSvg, stream, image, stretch);
                        }
                    }
                });
            m_writeAsyncOperations.push_back(streamWriteOperation);
            mustHideElement = false;
            return image;
        }

        // Otherwise, no resolver...
        if ((m_enableXamlImageHandling) || (m_listeners.size() == 0))
        {
            // If we've been explicitly told to let Xaml handle the image loading, or there are
            // no listeners waiting on the image load callbacks, use Xaml to load the images
            auto image = CreateImageSource(isImageSvg);

            if (isImageSvg)
            {
                // If we have an SVG, we need to try to parse for the image size before setting the image source
                auto svgDocumentLoadOperation = winrt::XmlDocument::LoadFromUriAsync(imageUrl);

                svgDocumentLoadOperation.Completed(
                    [weakThis = this->get_weak(),
                     weakImageSource = winrt::make_weak(image.as<winrt::SvgImageSource>()),
                     imageUrl](auto const& operation, auto status) -> void
                    {
                        auto strongThis = weakThis.get();
                        auto strongImageSource = weakImageSource.get();

                        if (strongThis && strongImageSource)
                        {
                            if (status == winrt::AsyncStatus::Completed)
                            {
                                strongThis->ParseXmlForHeightAndWidth(operation.GetResults(), strongImageSource);
                            }
                            // Now that we've parsed the height, we can set the image source
                            strongThis->SetSvgUriSource(strongImageSource, imageUrl);
                        }
                    });
            }
            else
            {
                image.as<winrt::BitmapImage>().UriSource(imageUrl);
            }

            SetImageSource(uiElement, image, stretch);

            // Issue #8126
            if (isAutoSize)
            {
                SetAutoSize(uiElement, parentElement, imageContainer, isVisible, true /* imageFiresOpenEvent */);
            }

            return image;
        }
        else
        {
            return PopulateImageFromUrlAsync(imageUrl, uiElement, isAutoSize, parentElement, imageContainer, isVisible, isImageSvg, stretch);
        }
    }

    winrt::ImageSource render_xaml::XamlBuilder::CreateImageSource(bool isImageSvg)
    {
        if (isImageSvg)
        {
            winrt::SvgImageSource svgImageSource{};
            return svgImageSource;
        }
        else
        {
            winrt::BitmapImage bitmapImage{};
            return bitmapImage;
        }
    }

    // Issue #8127
    template<typename T>
    winrt::ImageSource render_xaml::XamlBuilder::PopulateImageFromUrlAsync(winrt::Uri const& imageUrl,
                                                                           T const& uiElement,
                                                                           bool isAutoSize,
                                                                           winrt::IInspectable const& parentElement,
                                                                           winrt::IInspectable const& imageContainer,
                                                                           bool isVisible,
                                                                           bool isImageSvg,
                                                                           winrt::Stretch stretch)
    {
        winrt::HttpBaseProtocolFilter httpBaseProtocolFilter{};
        httpBaseProtocolFilter.AllowUI(false);

        winrt::HttpClient httpClient{httpBaseProtocolFilter};

        // Create an ImageSource to hold the image data.  We use BitmapImage & SvgImageSource in order to allow
        // the tracker to subscribe to the ImageLoaded/Failed events
        auto image = CreateImageSource(isImageSvg);
        this->m_imageLoadTracker->TrackImage(image);

        if (!isImageSvg)
        {
            image.as<winrt::BitmapImage>().CreateOptions(winrt::BitmapCreateOptions::None);
        }

        auto getStreamOperation = httpClient.GetInputStreamAsync(imageUrl);
        getStreamOperation.Completed(
            [this, weakThis = this->get_weak(), uiElement, parentElement, imageContainer, isAutoSize, isVisible, isImageSvg, image, stretch](
                auto const& operation, auto status) -> void
            {
                if (status == winrt::AsyncStatus::Completed)
                {
                    if (auto strongThis = weakThis.get())
                    {
                        auto imageStream = operation.GetResults();
                        winrt::InMemoryRandomAccessStream randomAccessStream{};
                        auto copyStreamOperation = winrt::RandomAccessStream::CopyAsync(imageStream, randomAccessStream);

                        m_copyStreamOperations.push_back(copyStreamOperation);

                        copyStreamOperation.Completed(
                            [randomAccessStream, weakThis, uiElement, parentElement, imageContainer, isAutoSize, isVisible, isImageSvg, image, stretch](
                                auto const& /*operation*/, auto status)
                            {
                                if (status == winrt::AsyncStatus::Completed)
                                {
                                    randomAccessStream.Seek(0);
                                    if (auto strongThis = weakThis.get())
                                    {
                                        strongThis->HandleAccessStreamForImageSource(
                                            uiElement, isAutoSize, parentElement, imageContainer, isVisible, isImageSvg, randomAccessStream, image, stretch);
                                    }
                                }
                            });
                    }
                }
            });
        m_getStreamOperations.push_back(getStreamOperation);

        return image;
    }

    template<typename T, typename S>
    void render_xaml::XamlBuilder::HandleAccessStreamForImageSource(T const& uiElement,
                                                                    bool isAutoSize,
                                                                    winrt::IInspectable const& parentElement,
                                                                    winrt::IInspectable const& imageContainer,
                                                                    bool isVisible,
                                                                    bool isImageSvg,
                                                                    S const& stream,
                                                                    winrt::ImageSource const& imageSource,
                                                                    winrt::Stretch stretch)
    {
        SetImageSource(uiElement, imageSource, stretch);

        if (isImageSvg)
        {
            // If we have an SVG, we need to try to parse for the image size before setting the image source
            auto streamSize = stream.Size();
            auto inputStream = stream.GetInputStreamAt(0);
            auto streamDataReader = winrt::DataReader(inputStream);
            auto loadDataReaderOperation = streamDataReader.LoadAsync((uint32_t)streamSize);

            auto temp = winrt::weak_ref(imageSource.as<winrt::SvgImageSource>());

            loadDataReaderOperation.Completed(
                [weakThis = this->get_weak(), streamDataReader, uiElementRef = winrt::make_weak(uiElement), isAutoSize, parentElementRef = winrt::make_weak(parentElement),
                imageContainerRef = winrt::make_weak(imageContainer), isVisible, streamRef = winrt::make_weak(stream),
                temp](
                    auto const& result, auto status) -> void
                {
                    auto strongThis = weakThis.get();
                    auto strongImageSource = temp.get();
                    auto strongStream = streamRef.get();
                    auto strongUiElement = uiElementRef.get();
                    auto strongParentElement = parentElementRef.get();
                    auto strongImageContainer = imageContainerRef.get();

                    if (strongThis && strongImageSource && strongStream && strongUiElement && strongParentElement && strongImageContainer)
                    {
                        if (status == winrt::AsyncStatus::Completed)
                        {
                            auto bytes = result.GetResults();
                            auto svgText = streamDataReader.ReadString(bytes);

                            auto svgDocument = winrt::XmlDocument();
                            svgDocument.LoadXml(svgText);

                            strongThis->ParseXmlForHeightAndWidth(svgDocument, strongImageSource);
                        }

                        // Now that we've parsed the height, we can set the image source
                        strongThis->SetSvgImageSourceAsync(
                            strongImageSource, strongStream, strongUiElement, isAutoSize, strongParentElement, strongImageContainer, isVisible);
                    }
                });
        }
        else
        {
            auto setSourceAction = imageSource.as<winrt::BitmapImage>().SetSourceAsync(stream);

            setSourceAction.Completed([weakThis = this->get_weak(), uiElement, isAutoSize, parentElement, imageContainer, isVisible](
                auto const& /*operation*/, auto status)
                {
                    if (status == winrt::AsyncStatus::Completed && isAutoSize)
                    {
                        if (auto strongThis = weakThis.get())
                        {
                            strongThis->SetAutoSize(uiElement, parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                        }
                    }
                });
        }
    }

    winrt::IAsyncAction render_xaml::XamlBuilder::SetSvgUriSource(winrt::SvgImageSource const imageSource,
                                                                  winrt::Uri const uri)
    {
        if (imageSource && uri)
        {
            co_await winrt::resume_foreground(imageSource.Dispatcher());
            imageSource.UriSource(uri);
        }
    }

    template<typename T, typename S>
    winrt::IAsyncAction render_xaml::XamlBuilder::SetSvgImageSourceAsync(winrt::SvgImageSource const imageSource,
                                                                         S const stream,
                                                                         T const uiElement,
                                                                         bool isAutoSize,
                                                                         winrt::IInspectable const parentElement,
                                                                         winrt::IInspectable const imageContainer,
                                                                         bool isVisible)
    {
            co_await winrt::resume_foreground(imageSource.Dispatcher());
            auto setSourceOperation = imageSource.SetSourceAsync(stream);

            setSourceOperation.Completed(
                [weakThis = this->get_weak(), uiElement, isAutoSize, parentElement, imageContainer, isVisible](
                    auto const& operation, auto status)
                {
                    auto loadStatus = operation.GetResults();
                    if (status == winrt::AsyncStatus::Completed && loadStatus == winrt::SvgImageSourceLoadStatus::Success)
                    {
                        if (auto strongThis = weakThis.get())
                        {
                            if (isAutoSize)
                            {
                                strongThis->SetAutoSize(uiElement, parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                            }
                        }
                    }
                });
    }

    template<typename T>
    void render_xaml::XamlBuilder::SetImageSource(T const& destination, winrt::ImageSource const& imageSource, winrt::Stretch /*stretch*/)
    {
        destination.Source(imageSource);
    };

    template<>
    void render_xaml::XamlBuilder::SetImageSource<winrt::Ellipse>(winrt::Ellipse const& destination,
                                                                  winrt::ImageSource const& imageSource,
                                                                  winrt::Stretch stretch)
    {
        winrt::ImageBrush imageBrush{};
        imageBrush.ImageSource(imageSource);

        imageBrush.Stretch(stretch);
        destination.Fill(imageBrush);
    };

    template<>
    void render_xaml::XamlBuilder::SetAutoSize<winrt::Ellipse>(winrt::Ellipse const& ellipse,
                                                               winrt::IInspectable const& parentElement,
                                                               winrt::IInspectable const& imageContainer,
                                                               bool isVisible,
                                                               bool imageFiresOpenEvent)
    {
        // Check if the image source fits in the parent container, if so, set the framework element's size to match the original image.
        if (parentElement && m_enableXamlImageHandling)
        {
            auto ellipseAsShape = imageContainer.as<winrt::Shape>();

            auto ellipseBrush = ellipseAsShape.Fill();

            auto brushAsImageBrush = ellipseBrush.as<winrt::ImageBrush>();

            auto imageSource = brushAsImageBrush.ImageSource();

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Ellipse while the image loads, so that resizing is not noticeable
                ellipse.Visibility(winrt::Visibility::Collapsed);

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                // Take a weak reference to the parent to avoid circular references (Parent->Ellipse->ImageBrush->Lambda->(Parent))
                auto weakParent = winrt::make_weak(parentElement);

                brushAsImageBrush.ImageOpened(
                    [ellipse, weakParent, isVisible](auto const& sender, auto /*args*/) -> void
                    {
                        if (isVisible)
                        {
                            auto lambdaBrushAsImageBrush = sender.as<winrt::ImageBrush>();

                            auto lambdaImageSource = lambdaBrushAsImageBrush.ImageSource();

                            auto lambdaParentElement = weakParent.get();
                            if (ellipse && lambdaParentElement)
                            {
                                winrt::FrameworkElement k{nullptr};
                                winrt::BitmapSource as{nullptr};

                                XamlHelpers::SetAutoImageSize(ellipse, lambdaParentElement, lambdaImageSource, isVisible);
                            }
                        }
                    });
            }
            else
            {
                XamlHelpers::SetAutoImageSize(ellipse, parentElement, imageSource, isVisible);
            }
        }
    }

    template<typename T>
    void render_xaml::XamlBuilder::SetAutoSize(T const& destination,
                                               winrt::IInspectable const& parentElement,
                                               winrt::IInspectable const&, /* imageContainer */
                                               bool isVisible,
                                               bool imageFiresOpenEvent)
    {
        if (parentElement && m_enableXamlImageHandling)
        {
            auto xamlImage = destination.as<winrt::Image>();
            auto imageSource = xamlImage.Source();

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Image control while the image loads, so that resizing is not noticeable
                xamlImage.Visibility(winrt::Visibility::Collapsed);

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                // Take weak references to the image and parent to avoid circular references between this lambda and
                // its parents (Parent->Image->Lambda->(Parent and Image))
                auto weakParent = winrt::make_weak(parentElement);

                auto weakImage = winrt::make_weak(xamlImage);

                xamlImage.ImageOpened(
                    [weakImage, weakParent, imageSource, isVisible](auto const& /*sender*/, auto const& /*args*/) -> void
                    {
                        if (const auto lambdaImageAsFrameworkElement = weakImage.get())
                        {
                            if (const auto lambdaParentElement = weakParent.get())
                            {
                                XamlHelpers::SetAutoImageSize(lambdaImageAsFrameworkElement, lambdaParentElement, imageSource, isVisible);
                            }
                        }
                    });
            }
            else
            {
                XamlHelpers::SetAutoImageSize(xamlImage, parentElement, imageSource, isVisible);
            }
        }
    }

    boolean render_xaml::XamlBuilder::IsSvgImage(std::string url)
    {
        // Question: is this check sufficient?
        auto foundSvg = url.find("svg");
        return !(foundSvg == std::string::npos);
    }

    void render_xaml::XamlBuilder::ParseXmlForHeightAndWidth(winrt::XmlDocument const& xmlDoc,
                                                             winrt::SvgImageSource const& imageSource)
    {
        if (xmlDoc)
        {
            auto rootElement = xmlDoc.DocumentElement();
            auto height = rootElement.GetAttribute(L"height");
            auto width = rootElement.GetAttribute(L"width");

            // We only need to set height or width, not both (fixes aspect ratio for person style)
            bool isHeightSet = false;

            if (!height.empty())
            {
                if (auto heightAsDouble = HStringToDouble(height))
                {
                    SetRasterizedPixelHeight(imageSource, heightAsDouble);
                    isHeightSet = true;
                }
            }

            if (!width.empty())
            {
                if (auto widthAsDouble = HStringToDouble(width))
                {
                    SetRasterizedPixelWidth(imageSource, widthAsDouble, isHeightSet);
                }
            }
        }
    }

    winrt::IAsyncAction render_xaml::XamlBuilder::SetRasterizedPixelHeight(winrt::SvgImageSource const imageSource,
                                                                           double imageSize,
                                                                           bool dropIfUnset)
    {
        co_await winrt::resume_foreground(imageSource.Dispatcher());
        auto currentSize = imageSource.RasterizePixelHeight();
        bool sizeIsUnset = isinf(currentSize);

        bool dropHeight = sizeIsUnset && dropIfUnset;

        if (!dropHeight)
        {
            imageSource.RasterizePixelHeight(imageSize);
        }
    }

    winrt::IAsyncAction render_xaml::XamlBuilder::SetRasterizedPixelWidth(winrt::SvgImageSource const imageSource,
                                                                          double imageSize,
                                                                          bool dropIfUnset)
    {
        co_await winrt::resume_foreground(imageSource.Dispatcher());
        auto currentSize = imageSource.RasterizePixelWidth();
        bool sizeIsUnset = isinf(currentSize);

        bool dropWidth = sizeIsUnset && dropIfUnset;

        if (!dropWidth)
        {
            imageSource.RasterizePixelWidth(imageSize);
        }
    }

    void render_xaml::XamlBuilder::SetRasterizedPixelHeight(winrt::ImageSource const& imageSource, double imageSize) {
        if (auto image = imageSource.try_as<winrt::SvgImageSource>())
        {
            auto currentSize = image.RasterizePixelHeight();
            bool sizeIsUnset = isinf(currentSize);

            if (sizeIsUnset)
            {
                image.RasterizePixelHeight(imageSize);
            }
        }
    }

    void render_xaml::XamlBuilder::SetRasterizedPixelWidth(winrt::ImageSource const& imageSource, double imageSize) {
        if (auto image = imageSource.try_as<winrt::SvgImageSource>())
        {
            auto currentSize = image.RasterizePixelWidth();
            bool sizeIsUnset = isinf(currentSize);

            if (sizeIsUnset)
            {
                image.RasterizePixelWidth(imageSize);
            }
        }
    }
}
