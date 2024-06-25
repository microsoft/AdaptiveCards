// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageRenderer.h"
#include "AdaptiveImageRenderer.g.cpp"

#include "ActionHelpers.h"
#include "AdaptiveBase64Util.h"
#include "AdaptiveCardGetResourceStreamArgs.h"
#include <robuffer.h>
#include "Util.h"
#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveImageRenderer::AdaptiveImageRenderer(winrt::com_ptr<::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder> xamlBuilder) :
        m_xamlBuilder(xamlBuilder)
    {
    }

    winrt::UIElement AdaptiveImageRenderer::Render(
        winrt::IAdaptiveCardElement const& cardElement, winrt::AdaptiveRenderContext const& renderContext, winrt::AdaptiveRenderArgs const& renderArgs)
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

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // IMPORTANT! Methods below here are actually XamlBuilder methods. They're defined here because they're only used
    // by the AdaptiveImageRenderer. They exist on XamlBuilder because it's the only place we have that can track
    // loading and lifetime for images.
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    winrt::UIElement XamlBuilder::BuildImage(
        winrt::IAdaptiveCardElement const& adaptiveCardElement,
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

        auto isImageSvg = IsSvgImage(imageUrl);

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

            auto imgProperties =
                ImageProperties<winrt::Ellipse>{ellipse, (size == winrt::ImageSize::Auto), parentElement, ellipseAsShape, isVisible, isImageSvg, imageStretch};

            imageSource = SetImageOnUIElement(imageUrl, resourceResolvers, imgProperties);

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

            auto imgProperties =
                ImageProperties<winrt::Image>{xamlImage, (size == winrt::ImageSize::Auto), parentElement, frameworkElement, isVisible, isImageSvg};

            imageSource = SetImageOnUIElement(imageUrl, resourceResolvers, imgProperties);
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

    winrt::IAsyncOperation<winrt::IRandomAccessStream> XamlBuilder::ResolveToStreamAsync(winrt::Uri const imageUrl,
        winrt::AdaptiveCardResourceResolvers const resolvers, bool const isImageSvg)
    {
        const auto weakThis = get_weak();
        const auto schemeName = imageUrl.SchemeName();

        if (resolvers)
        {
            auto resolver = resolvers.Get(schemeName);
            // If we have a resolver
            if (resolver)
            {
                auto args = winrt::make<winrt::implementation::AdaptiveCardGetResourceStreamArgs>(imageUrl);
                auto stream = co_await resolver.GetResourceStreamAsync(args);
                co_return stream;
            }
        }

        if (schemeName == L"data")
        {
            co_await winrt::resume_background();
            winrt::DataWriter dataWriter{winrt::InMemoryRandomAccessStream{}};
            auto imagePath = HStringToUTF8(imageUrl.Path());
            auto foundBase64 = imagePath.find("base64");
            if (foundBase64 != std::string::npos)
            {
                // Decode base 64 string
                std::string data = AdaptiveBase64Util::ExtractDataFromUri(imagePath);
                std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);
                dataWriter.WriteBytes(std::vector<byte>{decodedData.begin(), decodedData.end()});
            }
            else if (isImageSvg)
            {
                // Extract <svg> ... </svg> string
                std::string data = ExtractSvgDataFromUri(imageUrl);
                dataWriter.WriteBytes(std::vector<byte>{data.begin(), data.end()});
            }

            auto storeOp = dataWriter.StoreAsync();

            if (const auto strongThis = weakThis.get())
            {
                strongThis->m_writeAsyncOperations.push_back(storeOp);

                co_await storeOp;

                auto stream = dataWriter.DetachStream().try_as<winrt::InMemoryRandomAccessStream>();
                stream.Seek(0);

                co_return stream;
            }
        }

        // Otherwise, no resolver...
        if (auto strongThis = weakThis.get())
        {
            if (!(strongThis->m_enableXamlImageHandling) && (strongThis->m_listeners.size() == 0))
            {
                winrt::HttpBaseProtocolFilter httpBaseProtocolFilter{};
                httpBaseProtocolFilter.AllowUI(false);
                winrt::HttpClient httpClient{httpBaseProtocolFilter};
                auto getStreamOperation = httpClient.GetInputStreamAsync(imageUrl);
                strongThis->m_getStreamOperations.push_back(getStreamOperation);
                co_await getStreamOperation;

                auto imageStream = getStreamOperation.GetResults();
                winrt::InMemoryRandomAccessStream randomAccessStream{};
                auto copyStreamOperation = winrt::RandomAccessStream::CopyAsync(imageStream, randomAccessStream);
                strongThis->m_copyStreamOperations.push_back(copyStreamOperation);
                co_await copyStreamOperation;
                co_return randomAccessStream;
            }
        }

        co_return {};
    }

    template<typename TElement>
    winrt::fire_and_forget XamlBuilder::ResolveImageAsync(winrt::Uri const uri,
        winrt::AdaptiveCardResourceResolvers const resolvers,
        winrt::ImageSource imageSource,
        ImageProperties<TElement> const properties)
    {
        auto isAutoSize{properties.isAutoSize};
        auto isSVG{properties.isImageSvg};
        auto weakThis{get_weak()};
        auto weakImageSource{winrt::make_weak(imageSource)};
        auto weakFrameworkElement = winrt::make_weak(properties.uiElement);

        try
        {
            // if image loading is handled by Xaml, we set this to true;
            auto imageFiresOpenEvent{true};
            // we can not do any works until stream is resolved
            auto stream = co_await ResolveToStreamAsync(uri, resolvers, isSVG);
            if (auto strongImageSource = weakImageSource.get())
            {
                if (stream)
                {
                    imageFiresOpenEvent = false;

                    // the big differences between SVG and non-SVG images are:
                    // 1. SVG size needs to be parsed from its data source
                    // 2. SVG images need to be rasterized to a specific size
                    if (isSVG)
                    {
                        auto sizeParseOp{ParseSizeOfSVGImageFromStreamAsync(stream)};
                        // as size is being parsed, we can switch to the UI thread to set the source
                        co_await wil::resume_foreground(GetDispatcher(strongImageSource));
                        auto svgImageSource = strongImageSource.as<winrt::SvgImageSource>();

                        if (!isAutoSize)
                        {
                            auto size = co_await sizeParseOp;
                            svgImageSource.RasterizePixelHeight(size.Height);
                            svgImageSource.RasterizePixelWidth(size.Width);
                        }
                        svgImageSource.SetSourceAsync(stream);
                    }
                    else
                    {
                        co_await wil::resume_foreground(GetDispatcher(strongImageSource));
                        auto bitmapImage = strongImageSource.as<winrt::BitmapImage>();
                        bitmapImage.SetSourceAsync(stream);
                    }
                }
                else
                {
                    // Use Xaml to load the images 
                    if (auto strongThis = weakThis.get())
                    {
                        if ((strongThis->m_enableXamlImageHandling) || (strongThis->m_listeners.size() == 0))
                        {
                            // If we've been explicitly told to let Xaml handle the image loading, or there are
                            // no listeners waiting on the image load callbacks, use Xaml to load the images
                            if (isSVG)
                            {
                                winrt::HttpClient httpClient;
                                auto getOperation = co_await httpClient.GetAsync(uri);
                                auto readOperation = co_await getOperation.Content().ReadAsStringAsync();
                                auto size{ParseSizeOfSVGImageFromXmlString(readOperation)};
                                co_await wil::resume_foreground(GetDispatcher(strongImageSource));
                                auto svgImageSource = strongImageSource.as<winrt::SvgImageSource>();
                                svgImageSource.RasterizePixelHeight(size.Height);
                                svgImageSource.RasterizePixelWidth(size.Width);
                                svgImageSource.UriSource(uri);
                            }
                            else
                            {
                                co_await wil::resume_foreground(GetDispatcher(strongImageSource));
                                strongImageSource.as<winrt::BitmapImage>().UriSource(uri);
                            }
                        }
                    }
                }

                if (auto strongThis = weakThis.get(); isAutoSize)
                {
                    strongThis->SetAutoSize(
                        properties.uiElement,
                        properties.parentElement,
                        properties.imageContainer,
                        properties.isVisible,
                        imageFiresOpenEvent);
                }
            }
        }
       catch (...)
        {
            // Handle error
            if (auto strongThis = weakThis.get())
            {
                strongThis->m_imageLoadTracker->MarkFailedLoadImage(imageSource);
            }
        }
    }

    void XamlBuilder::ConfigureImageSource(winrt::Uri const& imageUrl,
                                        winrt::AdaptiveCardResourceResolvers const& resolvers,
                                        winrt::ImageSource const& imageSource,
                                        bool isImageSvg)
    {
        winrt::hstring schemeName = imageUrl.SchemeName();
        auto hasResolver = resolvers && resolvers.Get(schemeName) != nullptr;
        auto externalHandling = !(m_enableXamlImageHandling || (m_listeners.size() == 0));
        auto schemeNameIsData = schemeName == L"data";

        if (!isImageSvg)
        {
            if ((hasResolver || !schemeNameIsData) && externalHandling)
            {
                imageSource.as<winrt::BitmapImage>().CreateOptions(winrt::BitmapCreateOptions::None);
            }
            else if (schemeNameIsData)
            {
                imageSource.as<winrt::BitmapImage>().CreateOptions(winrt::BitmapCreateOptions::IgnoreImageCache);
            }
        }

        if ((hasResolver && externalHandling) || schemeNameIsData)
        {
            m_imageLoadTracker->TrackImage(imageSource);
        }
    }

    template<typename TElement>
    winrt::ImageSource XamlBuilder::SetImageOnUIElement(winrt::Uri const& imageUrl,
                                                        winrt::AdaptiveCardResourceResolvers const& resolvers,
                                                        ImageProperties<TElement> const& imgProperties)
    {
        auto imageSource = CreateImageSource(imgProperties.isImageSvg);

        SetImageSourceToFrameworkElement(imgProperties.uiElement, imageSource, imgProperties.stretch);

        ConfigureImageSource(imageUrl, resolvers, imageSource, imgProperties.isImageSvg);

        ResolveImageAsync(imageUrl, resolvers, imageSource, imgProperties);

        return imageSource;
    }

    winrt::ImageSource XamlBuilder::CreateImageSource(bool isImageSvg)
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

    template<typename TDest>
    void XamlBuilder::SetImageSourceToFrameworkElement(TDest const& destination, winrt::ImageSource const& imageSource, winrt::Stretch /*stretch*/)
    {
        destination.Source(imageSource);
    };

    template <>
    void XamlBuilder::SetImageSourceToFrameworkElement<winrt::Ellipse>(winrt::Ellipse const& destination, winrt::ImageSource const& imageSource, winrt::Stretch stretch)
    {
        winrt::ImageBrush imageBrush{};
        imageBrush.ImageSource(imageSource);

        imageBrush.Stretch(stretch);
        destination.Fill(imageBrush);
    };

    template <>
    void XamlBuilder::SetAutoSize<winrt::Ellipse>(
        winrt::Ellipse const& ellipse,
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

    template<typename TDest>
    void XamlBuilder::SetAutoSize(TDest const& destination,
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
 
    void XamlBuilder::SetRasterizedPixelHeight(winrt::ImageSource const& imageSource, double const& imageSize) {
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

    void XamlBuilder::SetRasterizedPixelWidth(winrt::ImageSource const& imageSource, double const& imageSize) {
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
