// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageRenderer.h"

#include "ActionHelpers.h"
#include "AdaptiveBase64Util.h"
#include "AdaptiveCardGetResourceStreamArgs.h"
#include <robuffer.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage;
using namespace ABI::Windows::Storage::Streams;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Text;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Data;
using namespace ABI::Windows::UI::Xaml::Documents;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::Web::Http;
using namespace ABI::Windows::Web::Http::Filters;

typedef ::AdaptiveCards::Rendering::WinUI3::XamlBuilder XamlBuilder;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveImageRenderer::AdaptiveImageRenderer() : m_xamlBuilder(winrt::make_self<XamlBuilder>()) {}

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

namespace AdaptiveCards::Rendering::WinUI3
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
        /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        RETURN_IF_FAILED(cardElement.As(&adaptiveImage));*/

        auto adaptiveImage = adaptiveCardElement.as<rtom::AdaptiveImage>();

        /* ComPtr<IAdaptiveHostConfig> hostConfig;
         RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

         HString url;
         RETURN_IF_FAILED(adaptiveImage->get_Url(url.GetAddressOf()));*/

        auto hostConfig = renderContext.HostConfig();
        auto url = adaptiveImage.Url();

        /*ComPtr<IUriRuntimeClass> imageUrl;
        GetUrlFromString(hostConfig.Get(), url.Get(), imageUrl.GetAddressOf());*/

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
        /* ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize size = ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize::None;*/
        rtom::ImageSize size = rtom::ImageSize::None;
        if (!hasExplicitMeasurements)
        {
            // RETURN_IF_FAILED(adaptiveImage->get_Size(&size));
            size = adaptiveImage.Size();
        }

        if (size == rtom::ImageSize::None && !hasExplicitMeasurements)
        {
            /* ComPtr<IAdaptiveImageConfig> imageConfig;
             RETURN_IF_FAILED(hostConfig->get_Image(&imageConfig));
             RETURN_IF_FAILED(imageConfig->get_ImageSize(&size));*/
            size = hostConfig.Image().ImageSize();
        }

        /* ABI::AdaptiveCards::ObjectModel::WinUI3::ImageStyle imageStyle;
         RETURN_IF_FAILED(adaptiveImage->get_Style(&imageStyle));
         ComPtr<IAdaptiveCardResourceResolvers> resourceResolvers;
         RETURN_IF_FAILED(renderContext->get_ResourceResolvers(&resourceResolvers));

         HString backgroundColor;
         RETURN_IF_FAILED(adaptiveImage->get_BackgroundColor(backgroundColor.GetAddressOf()));

         boolean isVisible;
         RETURN_IF_FAILED(adaptiveCardElement->get_IsVisible(&isVisible));*/

        auto imageStyle = adaptiveImage.Style();
        auto resourceResolvers = renderContext.ResourceResolvers();
        auto backgroundColor = adaptiveImage.BackgroundColor();
        // TODO: we can just use adaptiveImage here?
        auto isVisible = adaptiveCardElement.IsVisible();

        rtxaml::FrameworkElement frameworkElement{nullptr};

        // TODO: Not sure why it's been done this way
        // if (imageStyle == ImageStyle_Person)
        if (imageStyle == rtom::ImageStyle::Person)
        {
            /*ComPtr<IEllipse> ellipse =
                XamlHelpers::CreateABIClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));
            ComPtr<IEllipse> backgroundEllipse =
                XamlHelpers::CreateABIClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));*/
            rtxaml::Shapes::Ellipse ellipse{};
            rtxaml::Shapes::Ellipse backgroundEllipse{};

            rtxaml::Media::Stretch imageStretch =
                (isAspectRatioNeeded) ? rtxaml::Media::Stretch::Fill : rtxaml::Media::Stretch::UniformToFill;

            // bool mustHideElement{true};

            /*ComPtr<IInspectable> parentElement;
            RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));*/

            auto parentElement = renderArgs.ParentElement();

            // ComPtr<IShape> ellipseAsShape;
            // RETURN_IF_FAILED(ellipse.As(&ellipseAsShape));
            auto ellipseAsShape = ellipse.as<rtxaml::Shapes::Shape>();
            auto backgrondEllipseAsShape = backgroundEllipse.as<rtxaml::Shapes::Shape>();

            /* SetImageOnUIElement(imageUrl.Get(),
                                 ellipse.Get(),
                                 resourceResolvers.Get(),
                                 (size == ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize_Auto),
                                 parentElement.Get(),
                                 ellipseAsShape.Get(),
                                 isVisible,
                                 &mustHideElement,
                                 imageStretch);*/

            auto mustHideElement = SetImageOnUIElement(
                imageUrl, ellipse, resourceResolvers, (size == rtom::ImageSize::Auto), parentElement, ellipseAsShape, isVisible, imageStretch);

            /* ComPtr<IShape> backgroundEllipseAsShape;
             RETURN_IF_FAILED(backgroundEllipse.As(&backgroundEllipseAsShape));*/

            if (size == rtom::ImageSize::None || size == rtom::ImageSize::Stretch || size == rtom::ImageSize::Auto || hasExplicitMeasurements)
            {
                /* RETURN_IF_FAILED(ellipseAsShape->put_Stretch(imageStretch));
                 RETURN_IF_FAILED(backgroundEllipseAsShape->put_Stretch(imageStretch));*/
                ellipse.Stretch(imageStretch);
                backgroundEllipse.Stretch(imageStretch);
            }
            else
            {
                // Set the stretch for the ellipse - this is different to the stretch used for the image brush
                // above. This will force the ellipse to conform to fit within the confines of its parent.
                /*Stretch ellipseStretch = Stretch::Stretch_UniformToFill;
                RETURN_IF_FAILED(ellipseAsShape->put_Stretch(ellipseStretch));
                RETURN_IF_FAILED(backgroundEllipseAsShape->put_Stretch(ellipseStretch));*/
                ellipse.Stretch(rtxaml::Media::Stretch::UniformToFill);
                backgroundEllipse.Stretch(rtxaml::Media::Stretch::UniformToFill);
            }

            if (!backgroundColor.empty())
            {
                // Fill the background ellipse with solid color brush
                // ABI::Windows::UI::Color color;
                // RETURN_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor.Get()), &color));
                // ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                // RETURN_IF_FAILED(backgroundEllipseAsShape->put_Fill(backgroundColorBrush.Get()));

                //// Create a grid to contain the background color ellipse and the image ellipse
                // ComPtr<IGrid> imageGrid =
                //    XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));

                // ComPtr<IPanel> panel;
                // RETURN_IF_FAILED(imageGrid.As(&panel));

                // XamlHelpers::AppendXamlElementToPanel(backgroundEllipse.Get(), panel.Get());
                // XamlHelpers::AppendXamlElementToPanel(ellipse.Get(), panel.Get());

                // RETURN_IF_FAILED(imageGrid.As(&frameworkElement));

                auto color = GetColorFromString(HStringToUTF8(backgroundColor));
            }
            else
            {
                /*RETURN_IF_FAILED(ellipse.As(&frameworkElement));*/
                // TODO: I don't need to cast, do I?
                frameworkElement = ellipse.as<rtxaml::FrameworkElement>();
            }
        }
        else
        {
            /*ComPtr<IImage> xamlImage =
                XamlHelpers::CreateABIClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));*/
            rtxaml::Controls::Image xamlImage{};

            if (!backgroundColor.empty())
            {
                // Create a surrounding border with solid color background to contain the image
                /*ComPtr<IBorder> border =
                    XamlHelpers::CreateABIClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

                ABI::Windows::UI::Color color;
                RETURN_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor.Get()), &color));
                ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                RETURN_IF_FAILED(border->put_Background(backgroundColorBrush.Get()));

                ComPtr<IUIElement> imageAsUiElement;
                RETURN_IF_FAILED(xamlImage.CopyTo(imageAsUiElement.GetAddressOf()));
                RETURN_IF_FAILED(border->put_Child(imageAsUiElement.Get()));

                RETURN_IF_FAILED(border.As(&frameworkElement));*/
                rtxaml::Controls::Border border{};
                auto color = GetColorFromString(HStringToUTF8(backgroundColor));
                auto backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                border.Background(backgroundColorBrush);

                border.Child(xamlImage);

                frameworkElement = border.as<rtxaml::FrameworkElement>();
            }
            else
            {
                /*RETURN_IF_FAILED(xamlImage.As(&frameworkElement));*/
                frameworkElement = xamlImage.as<rtxaml::FrameworkElement>();
            }

            if (isAspectRatioNeeded)
            {
                xamlImage.Stretch(rtxaml::Media::Stretch::Fill);
            }

            /*ComPtr<IInspectable> parentElement;
            RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));

            bool mustHideElement{true};
            SetImageOnUIElement(imageUrl.Get(),
                                xamlImage.Get(),
                                resourceResolvers.Get(),
                                (size == ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize_Auto),
                                parentElement.Get(),
                                frameworkElement.Get(),
                                isVisible,
                                &mustHideElement);*/
            auto parentElement = renderArgs.ParentElement();
            bool mustHideElement =
                SetImageOnUIElement(imageUrl, xamlImage, resourceResolvers, (size == rtom::ImageSize::Auto), parentElement, frameworkElement, isVisible);

            // SetImageOnUIElement(imageUrl, xamlImage, resourceResolvers, (size == rtom::ImageSize::Auto),
            // parentElement, frameworkElement, isVisible, &mustHideElement);
        }

        /* ComPtr<IAdaptiveImageSizesConfig> sizeOptions;
         RETURN_IF_FAILED(hostConfig->get_ImageSizes(sizeOptions.GetAddressOf()));*/

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

        /* ComPtr<IReference<HAlignment>> adaptiveHorizontalAlignmentReference;
         RETURN_IF_FAILED(adaptiveImage->get_HorizontalAlignment(&adaptiveHorizontalAlignmentReference));*/
        auto adaptiveHorizontalAlignmentReference = adaptiveImage.HorizontalAlignment();

        // If the image doesn't have horizontal alignment set, check the render context for a parent value
        if (adaptiveHorizontalAlignmentReference == nullptr)
        {
            /* RETURN_IF_FAILED(renderContext->get_HorizontalContentAlignment(&adaptiveHorizontalAlignmentReference));*/
            adaptiveHorizontalAlignmentReference = renderContext.HorizontalContentAlignment();
        }

        auto adaptiveHorizontalAlignment = rtom::HAlignment::Left;
        if (adaptiveHorizontalAlignmentReference != nullptr)
        {
            /*RETURN_IF_FAILED(adaptiveHorizontalAlignmentReference->get_Value(&adaptiveHorizontalAlignment));*/
            adaptiveHorizontalAlignment = adaptiveHorizontalAlignmentReference.Value();
        }

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

        /*RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
        RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Image", frameworkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(adaptiveImage->get_SelectAction(&selectAction));

        ComPtr<IUIElement> imageAsUIElement;
        RETURN_IF_FAILED(frameworkElement.As(&imageAsUIElement));

        HString altText;
        RETURN_IF_FAILED(adaptiveImage->get_AltText(altText.GetAddressOf()));

        ComPtr<IDependencyObject> imageAsDependencyObject;
        RETURN_IF_FAILED(imageAsUIElement.As(&imageAsDependencyObject));

        ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
        RETURN_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationPropertiesStatics));

        RETURN_IF_FAILED(automationPropertiesStatics->SetName(imageAsDependencyObject.Get(), altText.Get()));

        ActionHelpers::HandleSelectAction(adaptiveCardElement,
                                          selectAction.Get(),
                                          renderContext,
                                          imageAsUIElement.Get(),
                                          XamlHelpers::SupportsInteractivity(hostConfig.Get()),
                                          true,
                                          imageControl);*/

        frameworkElement.VerticalAlignment(rtxaml::VerticalAlignment::Top);
        XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Image", frameworkElement);

        auto selectAction = adaptiveImage.SelectAction();

        winrt::hstring altText = adaptiveImage.AltText();

        rtxaml::Automation::AutomationProperties::SetName(frameworkElement, altText);

        return ActionHelpers::HandleSelectAction(
            adaptiveCardElement, selectAction, renderContext, frameworkElement, XamlHelpers::SupportsInteractivity(hostConfig), true);
    }

    template<typename T>
    bool XamlBuilder::SetImageOnUIElement(winrt::Windows::Foundation::Uri const& imageUrl,
                                          T const& uiElement,
                                          rtrender::AdaptiveCardResourceResolvers const& resolvers,
                                          bool isAutoSize,
                                          IInspectable const& parentElement,
                                          IInspectable const& imageContainer,
                                          bool isVisible,
                                          winrt::Windows::UI::Xaml::Media::Stretch stretch)
    {
        bool mustHideElement = true;

        // Get the image url scheme
        /* HString schemeName;
         THROW_IF_FAILED(imageUrl->get_SchemeName(schemeName.GetAddressOf()));*/
        // TODO: what if uri is nullptr? do we wanna fail?
        winrt::hstring schemeName = imageUrl.SchemeName();

        // Get the resolver for the image
        ComPtr<IAdaptiveCardResourceResolver> resolver;
        if (resolvers != nullptr)
        {
            /*THROW_IF_FAILED(resolvers->Get(schemeName.Get(), &resolver));*/
            auto resolver = resolvers.Get(schemeName);
            // If we have a resolver
            if (resolver != nullptr)
            {
                // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
                // the tracker to subscribe to the ImageLoaded/Failed events
                /*ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateABIClass<IBitmapImage>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));*/
                rtxaml::Media::Imaging::BitmapImage bitmapImage{};

                if (!m_enableXamlImageHandling && (m_listeners.size() != 0))
                {
                    this->m_imageLoadTracker->TrackBitmapImage(bitmapImage);
                }

                /* THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_None));
                 ComPtr<IBitmapSource> bitmapSource;
                 bitmapImage.As(&bitmapSource);*/
                bitmapImage.CreateOptions(rtxaml::Media::Imaging::BitmapCreateOptions::None);

                // Create the arguments to pass to the resolver
                auto args =
                    winrt::make<winrt::AdaptiveCards::Rendering::WinUI3::implementation::AdaptiveCardGetResourceStreamArgs>(imageUrl);

                // And call the resolver to get the image stream
                /*ComPtr<IAsyncOperation<IRandomAccessStream*>> getResourceStreamOperation;
                THROW_IF_FAILED(resolver->GetResourceStreamAsync(args.get(), &getResourceStreamOperation));*/
                auto getResourceStreamOperation = resolver.GetResourceStreamAsync(args);

                /*ComPtr<T> strongImageControl(uiElement);*/
                // ComPtr<XamlBuilder> strongThis(this);

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

                return;

                // getResourceStreamOperation.Completed(
                //    Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>,
                //    IAsyncOperationCompletedHandler<IRandomAccessStream*>>>(
                //        [strongThis, this, bitmapSource, strongImageControl, bitmapImage, stretch, isAutoSize,
                //        parentElement, imageContainer, isVisible](
                //            IAsyncOperation<IRandomAccessStream*>* operation, AsyncStatus status) -> HRESULT
                //        {
                //    if (status == AsyncStatus::Completed)
                //    {
                //        // Get the random access stream
                //        ComPtr<IRandomAccessStream> randomAccessStream;
                //        RETURN_IF_FAILED(operation->GetResults(&randomAccessStream));

                //        if (randomAccessStream == nullptr)
                //        {
                //            m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                //            return S_OK;
                //        }

                //        // Set the image source
                //        ComPtr<IImageSource> imageSource;
                //        RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                //        SetImageSource(strongImageControl.Get(), imageSource.Get(), stretch);

                //        ComPtr<IAsyncAction> setSourceAction;
                //        RETURN_IF_FAILED(bitmapSource->SetSourceAsync(randomAccessStream.Get(), &setSourceAction));

                //        auto callbackSource = Callback<IAsyncActionCompletedHandler>(
                //            [strongThis, this, strongImageControl, isAutoSize, parentElement, imageContainer,
                //            isVisible](
                //                IAsyncAction* /*action*/, AsyncStatus status) -> HRESULT
                //            {
                //                if (status == AsyncStatus::Completed)
                //                {
                //                    // Here should be the auto resizing, at this time we already have the image and
                //                    everything set if (isAutoSize)
                //                    {
                //                        SetAutoSize(strongImageControl.Get(), parentElement, imageContainer,
                //                        isVisible, false /* imageFiresOpenEvent */);
                //                    }
                //                }

                //                return S_OK;
                //            });

                //        RETURN_IF_FAILED(setSourceAction->put_Completed(callbackSource.Get()));

                //        return S_OK;
                //    }
                //    else
                //    {
                //        m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                //        return S_OK;
                //    }
                //        })
                //        .Get()));

                // return;
            }
        }

        /* INT32 isDataUriImage{};
         THROW_IF_FAILED(WindowsCompareStringOrdinal(schemeName.Get(), HStringReference(L"data").Get(), &isDataUriImage));*/
        if (schemeName == L"data")
        {
            // Decode base 64 string
            /*HString dataPath;
            THROW_IF_FAILED(imageUrl->get_Path(dataPath.GetAddressOf()));*/

            winrt::hstring dataPath = imageUrl.Path();

            std::string data = AdaptiveBase64Util::ExtractDataFromUri(HStringToUTF8(dataPath));
            std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);

            /*ComPtr<IBufferFactory> bufferFactory;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_Buffer).Get(),
                                                 bufferFactory.GetAddressOf()));

            ComPtr<IBuffer> buffer;
            THROW_IF_FAILED(bufferFactory->Create(static_cast<UINT32>(decodedData.size()), buffer.GetAddressOf()));*/

            winrt::Windows::Storage::Streams::Buffer buffer{static_cast<uint32_t>(decodedData.size())};

            /*ComPtr<::Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
            THROW_IF_FAILED(buffer.As(&bufferByteAccess));*/

            // BYTE* dataInternal{};
            // bufferByteAccess->Buffer(&dataInternal);

            memcpy_s(buffer.data(), decodedData.size(), decodedData.data(), decodedData.size());

            // THROW_IF_FAILED(buffer->put_Length(static_cast<UINT32>(decodedData.size())));
            buffer.Length(static_cast<uint32_t>(decodedData.size()));

            /*ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateABIClass<IBitmapImage>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
            m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
            THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_IgnoreImageCache));
            ComPtr<IBitmapSource> bitmapSource;
            THROW_IF_FAILED(bitmapImage.As(&bitmapSource));*/

            rtxaml::Media::Imaging::BitmapImage bitmapImage{};
            bitmapImage.CreateOptions(rtxaml::Media::Imaging::BitmapCreateOptions::IgnoreImageCache);

            /*ComPtr<IRandomAccessStream> randomAccessStream = XamlHelpers::CreateABIClass<IRandomAccessStream>(
                HStringReference(RuntimeClass_Windows_Storage_Streams_InMemoryRandomAccessStream));

            ComPtr<IOutputStream> outputStream;
            THROW_IF_FAILED(randomAccessStream.As(&outputStream));*/

            // TODO: Do I need to cast to output stream?
            winrt::Windows::Storage::Streams::InMemoryRandomAccessStream randomAccessStream{};
            auto bufferWriteOperation = randomAccessStream.WriteAsync(buffer);

            /* ComPtr<IAsyncOperationWithProgress<UINT32, UINT32>> bufferWriteOperation;
             THROW_IF_FAILED(outputStream->WriteAsync(buffer.Get(), &bufferWriteOperation));*/

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
            return;
            /* ComPtr<T> strongImageControl(uiElement);*/
            // ComPtr<XamlBuilder> strongThis(this);
            //
            // bufferWriteOperation->put_Completed(
            //    Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>,
            //    IAsyncOperationWithProgressCompletedHandler<UINT32, UINT32>>>(
            //        [strongThis, this, bitmapSource, randomAccessStream, strongImageControl, isAutoSize,
            //        parentElement, imageContainer, isVisible](
            //            IAsyncOperationWithProgress<UINT32, UINT32>* /*operation*/, AsyncStatus /*status*/) -> HRESULT
            //        {
            //            randomAccessStream->Seek(0);

            //            ComPtr<IImageSource> imageSource;
            //            RETURN_IF_FAILED(bitmapSource.As(&imageSource));

            //            SetImageSource(strongImageControl.Get(), imageSource.Get());

            //            ComPtr<IAsyncAction> setSourceAction;
            //            RETURN_IF_FAILED(bitmapSource->SetSourceAsync(randomAccessStream.Get(), &setSourceAction));

            //            auto callbackSource = Callback<IAsyncActionCompletedHandler>(
            //                [strongThis, this, strongImageControl, isAutoSize, parentElement, imageContainer,
            //                isVisible](
            //                    IAsyncAction* /*action*/, AsyncStatus status) -> HRESULT
            //                {
            //                    if (status == AsyncStatus::Completed)
            //                    {
            //                        if (isAutoSize)
            //                        {
            //                            SetAutoSize(strongImageControl.Get(), parentElement, imageContainer,
            //                            isVisible, false /* imageFiresOpenEvent */);
            //                        }
            //                    }

            //                    return S_OK;
            //                });

            //            RETURN_IF_FAILED(setSourceAction->put_Completed(callbackSource.Get()));

            //            return S_OK;
            //        })
            //        .Get()));

            // m_writeAsyncOperations.push_back(bufferWriteOperation);
            //*mustHideElement = false;
            // return;
        }

        // Otherwise, no resolver...
        if ((m_enableXamlImageHandling) || (m_listeners.size() == 0))
        {
            // If we've been explicitly told to let Xaml handle the image loading, or there are
            // no listeners waiting on the image load callbacks, use Xaml to load the images
            /* ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateABIClass<IBitmapImage>(
                 HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
             THROW_IF_FAILED(bitmapImage->put_UriSource(imageUrl));*/
            rtxaml::Media::Imaging::BitmapImage bitmapImage{};
            bitmapImage.UriSource(imageUrl);

            /*ComPtr<IImageSource> bitmapImageSource;
            THROW_IF_FAILED(bitmapImage.As(&bitmapImageSource));*/

            // SetImageSource(uiElement, bitmapImageSource.Get(), stretch);
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
        /*ComPtr<T> strongImageControl(imageControl);
        ComPtr<XamlBuilder> strongThis(this);*/
        getStreamOperation.Completed(
            [this, bitmapImage, imageControl](
                winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Storage::Streams::IInputStream,
                                                                        winrt::Windows::Web::Http::HttpProgress> const& operation,
                winrt::Windows::Foundation::AsyncStatus status) -> void // TODO: should it be void?)))
            {
                if (status == winrt::Windows::Foundation::AsyncStatus::Completed)
                {
                    auto imageStream = operation.GetResults();
                    // TODO: is it okay to instantiate a interface?
                    winrt::Windows::Storage::Streams::InMemoryRandomAccessStream randomAccessStream{};
                    auto copyStreamOperation = m_randomAccessStreamStatics.CopyAsync(imageStream, randomAccessStream);
                    m_copyStreamOperations.push_back(copyStreamOperation);

                    copyStreamOperation.Completed(
                        [this, bitmapImage, randomAccessStream, imageControl](
                            winrt::Windows::Foundation::IAsyncOperationWithProgress<uint64_t, uint64_t> const& /*operation*/,
                            winrt::Windows::Foundation::AsyncStatus /*status*/) { randomAccessStream.Seek(0); });
                }
            });
        m_getStreamOperations.push_back(getStreamOperation);
        // THROW_IF_FAILED(getStreamOperation->put_Completed(
        //    Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<IInputStream*, HttpProgress>>>(
        //        [strongThis, this, bitmapSource, strongImageControl, bitmapImage](
        //            IAsyncOperationWithProgress<IInputStream*, HttpProgress>* operation, AsyncStatus status) -> HRESULT
        //        {
        //            if (status == AsyncStatus::Completed)
        //            {
        //                // Load the image stream into an in memory random access stream, which is what
        //                // SetSource needs
        //                ComPtr<IInputStream> imageStream;
        //                RETURN_IF_FAILED(operation->GetResults(&imageStream));
        //                ComPtr<IRandomAccessStream> randomAccessStream = XamlHelpers::CreateABIClass<IRandomAccessStream>(
        //                    HStringReference(RuntimeClass_Windows_Storage_Streams_InMemoryRandomAccessStream));
        //                ComPtr<IOutputStream> outputStream;
        //                RETURN_IF_FAILED(randomAccessStream.As(&outputStream));
        //                ComPtr<IAsyncOperationWithProgress<UINT64, UINT64>> copyStreamOperation;
        //                RETURN_IF_FAILED(m_randomAccessStreamStatics->CopyAsync(imageStream.Get(), outputStream.Get(), &copyStreamOperation));

        //                m_copyStreamOperations.push_back(copyStreamOperation);
        //                return copyStreamOperation->put_Completed(
        //                    Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>,
        //                    IAsyncOperationWithProgressCompletedHandler<UINT64, UINT64>>>(
        //                        [strongThis, this, bitmapSource, randomAccessStream, strongImageControl](
        //                            IAsyncOperationWithProgress<UINT64, UINT64>* /*operation*/, AsyncStatus
        //                            /*status*/) -> HRESULT
        //                        {
        //                            randomAccessStream->Seek(0);

        //                            ComPtr<IImageSource> imageSource;
        //                            RETURN_IF_FAILED(bitmapSource.As(&imageSource));

        //                            SetImageSource(strongImageControl.Get(), imageSource.Get());
        //                            ComPtr<IAsyncAction> setSourceAction;
        //                            RETURN_IF_FAILED(bitmapSource->SetSourceAsync(randomAccessStream.Get(), &setSourceAction));

        //                            return S_OK;
        //                        })
        //                        .Get());
        //            }
        //            else
        //            {
        //                m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
        //                return S_OK;
        //            }
        //        })
        //        .Get()));
        // m_getStreamOperations.push_back(getStreamOperation);
    }

    template<typename T>
    void XamlBuilder::SetImageSource(T const& destination, rtxaml::Media::ImageSource const& imageSource, rtxaml::Media::Stretch stretch /*stretch*/)
    {
        /*THROW_IF_FAILED(destination->put_Source(imageSource));*/
        destination.Source(imageSource);
    };

    template<>
    void XamlBuilder::SetImageSource<rtxaml::Shapes::Ellipse>(rtxaml::Shapes::Ellipse const& destination,
                                                              rtxaml::Media::ImageSource const& imageSource,
                                                              rtxaml::Media::Stretch stretch)
    {
        /* ComPtr<IImageBrush> imageBrush =
             XamlHelpers::CreateABIClass<IImageBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_ImageBrush));
         THROW_IF_FAILED(imageBrush->put_ImageSource(imageSource));*/

        rtxaml::Media::ImageBrush imageBrush{};
        imageBrush.ImageSource(imageSource);

        /*ComPtr<ITileBrush> tileBrush;
        THROW_IF_FAILED(imageBrush.As(&tileBrush));
        THROW_IF_FAILED(tileBrush->put_Stretch(stretch));*/
        imageBrush.Stretch(stretch);

        /* ComPtr<IBrush> brush;
         THROW_IF_FAILED(imageBrush.As(&brush));*/

        /*ComPtr<IShape> ellipseAsShape;
        ComPtr<IEllipse> ellipse(destination);
        THROW_IF_FAILED(ellipse.As(&ellipseAsShape));

        THROW_IF_FAILED(ellipseAsShape->put_Fill(brush.Get()));*/
        destination.Fill(imageBrush);
    };

    template<>
    void XamlBuilder::SetAutoSize<rtxaml::Shapes::Ellipse>(rtxaml::Shapes::Ellipse const& destination,
                                                           IInspectable const& parentElement,
                                                           IInspectable const& imageContainer,
                                                           bool isVisible,
                                                           bool imageFiresOpenEvent)
    {
        // Check if the image source fits in the parent container, if so, set the framework element's size to match the original image.
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            /* ComPtr<IInspectable> ellipseShape(imageContainer);
             ComPtr<IShape> ellipseAsShape;
             THROW_IF_FAILED(ellipseShape.As(&ellipseAsShape));*/

            /*  ComPtr<IBrush> ellipseBrush;
              THROW_IF_FAILED(ellipseAsShape->get_Fill(&ellipseBrush));
              ComPtr<IImageBrush> brushAsImageBrush;
              THROW_IF_FAILED(ellipseBrush.As(&brushAsImageBrush));*/
            auto ellipseAsShape = imageContainer.as<rtxaml::Shapes::Shape>();

            auto ellipseBrush = ellipseAsShape.Fill();

            auto brushAsImageBrush = ellipseBrush.as<rtxaml::Media::ImageBrush>();

            /* ComPtr<IEllipse> ellipse(destination);

             ComPtr<IUIElement> ellipseAsUIElement;
             THROW_IF_FAILED(ellipse.As(&ellipseAsUIElement));

             ComPtr<IFrameworkElement> ellipseAsFrameworkElement;
             THROW_IF_FAILED(ellipse.As(&ellipseAsFrameworkElement));*/

            /*ComPtr<IImageSource> imageSource;
            THROW_IF_FAILED(brushAsImageBrush->get_ImageSource(&imageSource));
            ComPtr<IBitmapSource> imageSourceAsBitmap;
            THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));*/

            auto imageSource = brushAsImageBrush.ImageSource();
            auto imageSourceAsBitmap = imageSource.as<rtxaml::Media::Imaging::BitmapSource>();

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Ellipse while the image loads, so that resizing is not noticeable
                /* THROW_IF_FAILED(ellipseAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));*/
                ellipseAsShape.Visibility(rtxaml::Visibility::Collapsed);

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                // TODO: what's the point of eventToken if we don';t save it ?
                // EventRegistrationToken eventToken;
                // ComPtr<IInspectable> localParentElement(parentElement);

                // Take a weak reference to the parent to avoid circular references (Parent->Ellipse->ImageBrush->Lambda->(Parent))
                /*WeakRef weakParent;
                THROW_IF_FAILED(localParentElement.AsWeak(&weakParent));*/

                auto weakParent = winrt::make_weak(parentElement);

                // THROW_IF_FAILED(brushAsImageBrush->add_ImageOpened(
                //    Callback<IRoutedEventHandler>(
                //        [ellipseAsFrameworkElement, weakParent, isVisible](IInspectable* sender, IRoutedEventArgs*
                //                                                           /*args*/) -> HRESULT
                // TODO: do we need a revoker/token?
                brushAsImageBrush.ImageOpened(
                    [ellipseAsShape, weakParent, isVisible](winrt::Windows::Foundation::IInspectable const& sender,
                                                            rtxaml::RoutedEventArgs /*args*/) -> void
                    {
                        if (isVisible)
                        {
                            /*ComPtr<IImageBrush> lambdaBrushAsImageBrush;
                            RETURN_IF_FAILED(sender->QueryInterface(IID_PPV_ARGS(&lambdaBrushAsImageBrush)));*/
                            auto lambdaBrushAsImageBrush = sender.as<rtxaml::Media::ImageBrush>();

                            /*ComPtr<IImageSource> lambdaImageSource;
                            RETURN_IF_FAILED(lambdaBrushAsImageBrush->get_ImageSource(&lambdaImageSource));
                            ComPtr<IBitmapSource> lambdaImageSourceAsBitmap;
                            RETURN_IF_FAILED(lambdaImageSource.As(&lambdaImageSourceAsBitmap));*/
                            auto lambdaImageSource = lambdaBrushAsImageBrush.ImageSource();
                            auto lamdaImageSourceAsBitmap = lambdaImageSource.as<rtxaml::Media::Imaging::BitmapSource>();

                            /* ComPtr<IInspectable> lambdaParentElement;
                             RETURN_IF_FAILED(weakParent.As(&lambdaParentElement));*/
                            auto lambdaParentElement = weakParent.get();
                            /*if (ellipseAsFrameworkElement.Get() && lambdaParentElement)*/
                            // TODO: no reason to convert ellipse to framework element, because  FE -> Shape - cast will
                            // be successfull if ellipseAsShape is not null
                            if (ellipseAsShape && lambdaParentElement)
                            {
                                rtxaml::FrameworkElement k{nullptr};
                                IInspectable whatever{};
                                rtxaml::Media::Imaging::BitmapSource as{nullptr};


                                XamlHelpers::SetAutoImageSize(ellipseAsShape,
                                                              lambdaParentElement,
                                                              lamdaImageSourceAsBitmap,
                                                              isVisible);
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
                                  IInspectable const& parentElement,
                                  IInspectable const&, /* imageContainer */
                                  bool isVisible,
                                  bool imageFiresOpenEvent)
    {
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            /*ComPtr<IImage> xamlImage(destination);*/
            auto xamlImage = destination.as<rtxaml::Controls::Image>();
            /* ComPtr<IFrameworkElement> imageAsFrameworkElement;
             THROW_IF_FAILED(xamlImage.As(&imageAsFrameworkElement));
             ComPtr<IImageSource> imageSource;
             THROW_IF_FAILED(xamlImage->get_Source(&imageSource));
             ComPtr<IBitmapSource> imageSourceAsBitmap;
             THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));

             ComPtr<IUIElement> imageAsUIElement;
             THROW_IF_FAILED(xamlImage.As(&imageAsUIElement));*/
            auto imageSource = xamlImage.Source();

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Image control while the image loads, so that resizing is not noticeable
                /* THROW_IF_FAILED(imageAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));*/
                xamlImage.Visibility(rtxaml::Visibility::Collapsed);

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                /*ComPtr<IInspectable> localParentElement(parentElement);*/

                // Take weak references to the image and parent to avoid circular references between this lambda and
                // its parents (Parent->Image->Lambda->(Parent and Image))
                /*WeakRef weakParent;
                THROW_IF_FAILED(localParentElement.AsWeak(&weakParent));*/
                auto weakParent = winrt::make_weak(parentElement);

                /* WeakRef weakImage;
                 THROW_IF_FAILED(imageAsFrameworkElement.AsWeak(&weakImage));*/
                auto weakImage = winrt::make_weak(xamlImage);
                /* EventRegistrationToken eventToken;
                 THROW_IF_FAILED(xamlImage->add_ImageOpened(
                     Callback<IRoutedEventHandler>(*/
                xamlImage.ImageOpened(
                    [weakImage, weakParent, imageSource, isVisible](winrt::Windows::Foundation::IInspectable const& /*sender*/,
                                                                    rtxaml::RoutedEventArgs const&
                                                                    /*args*/) -> void
                    {
                        /*ComPtr<IFrameworkElement> lambdaImageAsFrameworkElement;
                        RETURN_IF_FAILED(weakImage.As(&lambdaImageAsFrameworkElement));

                        ComPtr<IInspectable> lambdaParentElement;
                        RETURN_IF_FAILED(weakParent.As(&lambdaParentElement));*/

                        auto lambdaImageAsFrameworkElement = weakImage.get();
                        auto lambdaParentElement = weakParent.get();

                        if (lambdaImageAsFrameworkElement && lambdaParentElement)
                        {
                            XamlHelpers::SetAutoImageSize(lambdaImageAsFrameworkElement,
                                                                           lambdaParentElement,
                                                                           imageSource),
                                                                           isVisible);
                        }
                    });
            }
            else
            {
                XamlHelpers::SetAutoImageSize(imageAsFrameworkElement, parentElement, imageSource, isVisible);
            }
        }
    }
}
