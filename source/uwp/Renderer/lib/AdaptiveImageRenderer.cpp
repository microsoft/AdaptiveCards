// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageRenderer.h"

#include "ActionHelpers.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveImage.h"
#include "AdaptiveBase64Util.h"
#include "AdaptiveCardGetResourceStreamArgs.h"
#include <robuffer.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
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

namespace AdaptiveNamespace
{
    AdaptiveImageRenderer::AdaptiveImageRenderer() {}

    AdaptiveImageRenderer::AdaptiveImageRenderer(ComPtr<XamlBuilder> xamlBuilder) : m_xamlBuilder(xamlBuilder) {}

    HRESULT AdaptiveImageRenderer::RuntimeClassInitialize() noexcept
    try
    {
        RETURN_IF_FAILED(MakeAndInitialize<XamlBuilder>(&m_xamlBuilder));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveImageRenderer::Render(_In_ IAdaptiveCardElement* cardElement,
                                          _In_ IAdaptiveRenderContext* renderContext,
                                          _In_ IAdaptiveRenderArgs* renderArgs,
                                          _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept
    try
    {
        return m_xamlBuilder->BuildImage(cardElement, renderContext, renderArgs, result);
    }
    CATCH_RETURN;

    HRESULT AdaptiveImageRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept
    try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveImage, AdaptiveSharedNamespace::Image, AdaptiveSharedNamespace::ImageParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // IMPORTANT! Methods below here are actually XamlBuilder methods. They're defined here because they're only used
    // by the AdaptiveImageRenderer. They exist on XamlBuilder because it's the only place we have that can track
    // loading and lifetime for images.
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    HRESULT XamlBuilder::BuildImage(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    _In_ IAdaptiveRenderArgs* renderArgs,
                                    _COM_Outptr_ IUIElement** imageControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        RETURN_IF_FAILED(cardElement.As(&adaptiveImage));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        HString url;
        RETURN_IF_FAILED(adaptiveImage->get_Url(url.GetAddressOf()));

        ComPtr<IUriRuntimeClass> imageUrl;
        GetUrlFromString(hostConfig.Get(), url.Get(), imageUrl.GetAddressOf());

        if (imageUrl == nullptr)
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::AssetLoadFailed,
                                      HStringReference(L"Image not found").Get());
            *imageControl = nullptr;
            return S_OK;
        }

        UINT32 pixelWidth = 0, pixelHeight = 0;
        RETURN_IF_FAILED(adaptiveImage->get_PixelWidth(&pixelWidth));
        RETURN_IF_FAILED(adaptiveImage->get_PixelHeight(&pixelHeight));
        bool hasExplicitMeasurements = (pixelWidth || pixelHeight);
        bool isAspectRatioNeeded = (pixelWidth && pixelHeight);

        // Get the image's size and style
        ABI::AdaptiveNamespace::ImageSize size = ABI::AdaptiveNamespace::ImageSize::None;
        if (!hasExplicitMeasurements)
        {
            RETURN_IF_FAILED(adaptiveImage->get_Size(&size));
        }

        if (size == ABI::AdaptiveNamespace::ImageSize::None && !hasExplicitMeasurements)
        {
            ComPtr<IAdaptiveImageConfig> imageConfig;
            RETURN_IF_FAILED(hostConfig->get_Image(&imageConfig));
            RETURN_IF_FAILED(imageConfig->get_ImageSize(&size));
        }

        ABI::AdaptiveNamespace::ImageStyle imageStyle;
        RETURN_IF_FAILED(adaptiveImage->get_Style(&imageStyle));
        ComPtr<IAdaptiveCardResourceResolvers> resourceResolvers;
        RETURN_IF_FAILED(renderContext->get_ResourceResolvers(&resourceResolvers));

        HString backgroundColor;
        RETURN_IF_FAILED(adaptiveImage->get_BackgroundColor(backgroundColor.GetAddressOf()));

        boolean isVisible;
        RETURN_IF_FAILED(adaptiveCardElement->get_IsVisible(&isVisible));

        ComPtr<IFrameworkElement> frameworkElement;
        if (imageStyle == ImageStyle_Person)
        {
            ComPtr<IEllipse> ellipse =
                XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));
            ComPtr<IEllipse> backgroundEllipse =
                XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));

            Stretch imageStretch = (isAspectRatioNeeded) ? Stretch::Stretch_Fill : Stretch::Stretch_UniformToFill;
            bool mustHideElement{true};

            ComPtr<IInspectable> parentElement;
            RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));

            ComPtr<IShape> ellipseAsShape;
            RETURN_IF_FAILED(ellipse.As(&ellipseAsShape));

            SetImageOnUIElement(imageUrl.Get(),
                                ellipse.Get(),
                                resourceResolvers.Get(),
                                (size == ABI::AdaptiveNamespace::ImageSize_Auto),
                                parentElement.Get(),
                                ellipseAsShape.Get(),
                                isVisible,
                                &mustHideElement,
                                imageStretch);

            ComPtr<IShape> backgroundEllipseAsShape;
            RETURN_IF_FAILED(backgroundEllipse.As(&backgroundEllipseAsShape));

            if (size == ABI::AdaptiveNamespace::ImageSize::None || size == ABI::AdaptiveNamespace::ImageSize::Stretch ||
                size == ABI::AdaptiveNamespace::ImageSize::Auto || hasExplicitMeasurements)
            {
                RETURN_IF_FAILED(ellipseAsShape->put_Stretch(imageStretch));
                RETURN_IF_FAILED(backgroundEllipseAsShape->put_Stretch(imageStretch));
            }
            else
            {
                // Set the stretch for the ellipse - this is different to the stretch used for the image brush
                // above. This will force the ellipse to conform to fit within the confines of its parent.
                Stretch ellipseStretch = Stretch::Stretch_UniformToFill;
                RETURN_IF_FAILED(ellipseAsShape->put_Stretch(ellipseStretch));
                RETURN_IF_FAILED(backgroundEllipseAsShape->put_Stretch(ellipseStretch));
            }

            if (backgroundColor.Get() != nullptr)
            {
                // Fill the background ellipse with solid color brush
                ABI::Windows::UI::Color color;
                RETURN_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor.Get()), &color));
                ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                RETURN_IF_FAILED(backgroundEllipseAsShape->put_Fill(backgroundColorBrush.Get()));

                // Create a grid to contain the background color ellipse and the image ellipse
                ComPtr<IGrid> imageGrid =
                    XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));

                ComPtr<IPanel> panel;
                RETURN_IF_FAILED(imageGrid.As(&panel));

                XamlHelpers::AppendXamlElementToPanel(backgroundEllipse.Get(), panel.Get());
                XamlHelpers::AppendXamlElementToPanel(ellipse.Get(), panel.Get());

                RETURN_IF_FAILED(imageGrid.As(&frameworkElement));
            }
            else
            {
                RETURN_IF_FAILED(ellipse.As(&frameworkElement));
            }
        }
        else
        {
            ComPtr<IImage> xamlImage =
                XamlHelpers::CreateXamlClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));

            if (backgroundColor != nullptr)
            {
                // Create a surrounding border with solid color background to contain the image
                ComPtr<IBorder> border =
                    XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

                ABI::Windows::UI::Color color;
                RETURN_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor.Get()), &color));
                ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                RETURN_IF_FAILED(border->put_Background(backgroundColorBrush.Get()));

                ComPtr<IUIElement> imageAsUiElement;
                RETURN_IF_FAILED(xamlImage.CopyTo(imageAsUiElement.GetAddressOf()));
                RETURN_IF_FAILED(border->put_Child(imageAsUiElement.Get()));

                RETURN_IF_FAILED(border.As(&frameworkElement));
            }
            else
            {
                RETURN_IF_FAILED(xamlImage.As(&frameworkElement));
            }

            if (isAspectRatioNeeded)
            {
                xamlImage->put_Stretch(Stretch::Stretch_Fill);
            }

            ComPtr<IInspectable> parentElement;
            RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));

            bool mustHideElement{true};
            SetImageOnUIElement(imageUrl.Get(),
                                xamlImage.Get(),
                                resourceResolvers.Get(),
                                (size == ABI::AdaptiveNamespace::ImageSize_Auto),
                                parentElement.Get(),
                                frameworkElement.Get(),
                                isVisible,
                                &mustHideElement);
        }

        ComPtr<IAdaptiveImageSizesConfig> sizeOptions;
        RETURN_IF_FAILED(hostConfig->get_ImageSizes(sizeOptions.GetAddressOf()));

        if (hasExplicitMeasurements)
        {
            if (pixelWidth)
            {
                if (imageStyle == ImageStyle_Person)
                {
                    RETURN_IF_FAILED(frameworkElement->put_Width(pixelWidth));
                }
                else
                {
                    RETURN_IF_FAILED(frameworkElement->put_MaxWidth(pixelWidth));
                }
            }

            if (pixelHeight)
            {
                if (imageStyle == ImageStyle_Person)
                {
                    RETURN_IF_FAILED(frameworkElement->put_Height(pixelHeight));
                }
                else
                {
                    RETURN_IF_FAILED(frameworkElement->put_MaxHeight(pixelHeight));
                }
            }
        }
        else
        {
            if (size == ABI::AdaptiveNamespace::ImageSize::Small || size == ABI::AdaptiveNamespace::ImageSize::Medium ||
                size == ABI::AdaptiveNamespace::ImageSize::Large)
            {
                UINT32 imageSize;
                switch (size)
                {
                case ABI::AdaptiveNamespace::ImageSize::Small:
                {
                    RETURN_IF_FAILED(sizeOptions->get_Small(&imageSize));
                    break;
                }

                case ABI::AdaptiveNamespace::ImageSize::Medium:
                {
                    RETURN_IF_FAILED(sizeOptions->get_Medium(&imageSize));
                    break;
                }

                case ABI::AdaptiveNamespace::ImageSize::Large:
                {
                    RETURN_IF_FAILED(sizeOptions->get_Large(&imageSize));

                    break;
                }
                default:
                {
                    return E_UNEXPECTED;
                }
                }

                RETURN_IF_FAILED(frameworkElement->put_MaxWidth(imageSize));

                // We don't want to set a max height on the person ellipse as ellipses do not understand preserving
                // aspect ratio when constrained on both axes.
                if (imageStyle != ImageStyle_Person)
                {
                    RETURN_IF_FAILED(frameworkElement->put_MaxHeight(imageSize));
                }
            }
        }

        ABI::AdaptiveNamespace::HAlignment adaptiveHorizontalAlignment;
        RETURN_IF_FAILED(adaptiveImage->get_HorizontalAlignment(&adaptiveHorizontalAlignment));

        switch (adaptiveHorizontalAlignment)
        {
        case ABI::AdaptiveNamespace::HAlignment::Left:
            RETURN_IF_FAILED(frameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Left));
            break;
        case ABI::AdaptiveNamespace::HAlignment::Right:
            RETURN_IF_FAILED(frameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Right));
            break;
        case ABI::AdaptiveNamespace::HAlignment::Center:
            RETURN_IF_FAILED(frameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Center));
            break;
        }

        RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
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
                                          imageControl);

        return S_OK;
    }

    template<typename T>
    void XamlBuilder::SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl,
                                          _In_ T* uiElement,
                                          _In_opt_ IAdaptiveCardResourceResolvers* resolvers,
                                          bool isAutoSize,
                                          IInspectable* parentElement,
                                          IInspectable* imageContainer,
                                          bool isVisible,
                                          _Out_ bool* mustHideElement,
                                          ABI::Windows::UI::Xaml::Media::Stretch stretch)
    {
        *mustHideElement = true;

        // Get the image url scheme
        HString schemeName;
        THROW_IF_FAILED(imageUrl->get_SchemeName(schemeName.GetAddressOf()));

        // Get the resolver for the image
        ComPtr<IAdaptiveCardResourceResolver> resolver;
        if (resolvers != nullptr)
        {
            THROW_IF_FAILED(resolvers->Get(schemeName.Get(), &resolver));
            // If we have a resolver
            if (resolver != nullptr)
            {
                // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
                // the tracker to subscribe to the ImageLoaded/Failed events
                ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));

                if (!m_enableXamlImageHandling && (m_listeners.size() != 0))
                {
                    m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
                }

                THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_None));
                ComPtr<IBitmapSource> bitmapSource;
                bitmapImage.As(&bitmapSource);

                // Create the arguments to pass to the resolver
                ComPtr<IAdaptiveCardGetResourceStreamArgs> args;
                THROW_IF_FAILED(MakeAndInitialize<AdaptiveCardGetResourceStreamArgs>(&args, imageUrl));

                // And call the resolver to get the image stream
                ComPtr<IAsyncOperation<IRandomAccessStream*>> getResourceStreamOperation;
                THROW_IF_FAILED(resolver->GetResourceStreamAsync(args.Get(), &getResourceStreamOperation));

                ComPtr<T> strongImageControl(uiElement);
                ComPtr<XamlBuilder> strongThis(this);
                THROW_IF_FAILED(getResourceStreamOperation->put_Completed(
                    Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationCompletedHandler<IRandomAccessStream*>>>(
                        [strongThis, this, bitmapSource, strongImageControl, bitmapImage, stretch, isAutoSize, parentElement, imageContainer, isVisible](
                            IAsyncOperation<IRandomAccessStream*>* operation, AsyncStatus status) -> HRESULT {
                            if (status == AsyncStatus::Completed)
                            {
                                // Get the random access stream
                                ComPtr<IRandomAccessStream> randomAccessStream;
                                RETURN_IF_FAILED(operation->GetResults(&randomAccessStream));

                                if (randomAccessStream == nullptr)
                                {
                                    m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                                    return S_OK;
                                }

                                RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                                ComPtr<IImageSource> imageSource;
                                RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                                SetImageSource(strongImageControl.Get(), imageSource.Get(), stretch);

                                // Here should be the auto resizing, at this time we already have the image and everything set
                                if (isAutoSize)
                                {
                                    SetAutoSize(strongImageControl.Get(), parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                                }

                                return S_OK;
                            }
                            else
                            {
                                m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                                return S_OK;
                            }
                        })
                        .Get()));

                return;
            }
        }

        INT32 isDataUriImage{};
        THROW_IF_FAILED(WindowsCompareStringOrdinal(schemeName.Get(), HStringReference(L"data").Get(), &isDataUriImage));
        if (isDataUriImage == 0)
        {
            // Decode base 64 string
            HString dataPath;
            THROW_IF_FAILED(imageUrl->get_Path(dataPath.GetAddressOf()));

            std::string data = AdaptiveBase64Util::ExtractDataFromUri(HStringToUTF8(dataPath.Get()));
            std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);

            ComPtr<IBufferFactory> bufferFactory;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_Buffer).Get(),
                                                 bufferFactory.GetAddressOf()));

            ComPtr<IBuffer> buffer;
            THROW_IF_FAILED(bufferFactory->Create(static_cast<UINT32>(decodedData.size()), buffer.GetAddressOf()));

            ComPtr<::Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
            THROW_IF_FAILED(buffer.As(&bufferByteAccess));

            BYTE* dataInternal{};
            THROW_IF_FAILED(bufferByteAccess->Buffer(&dataInternal));

            memcpy_s(dataInternal, decodedData.size(), decodedData.data(), decodedData.size());

            THROW_IF_FAILED(buffer->put_Length(static_cast<UINT32>(decodedData.size())));

            ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
            m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
            THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_IgnoreImageCache));
            ComPtr<IBitmapSource> bitmapSource;
            THROW_IF_FAILED(bitmapImage.As(&bitmapSource));

            ComPtr<IRandomAccessStream> randomAccessStream = XamlHelpers::CreateXamlClass<IRandomAccessStream>(
                HStringReference(RuntimeClass_Windows_Storage_Streams_InMemoryRandomAccessStream));

            ComPtr<IOutputStream> outputStream;
            THROW_IF_FAILED(randomAccessStream.As(&outputStream));

            ComPtr<IAsyncOperationWithProgress<UINT32, UINT32>> bufferWriteOperation;
            THROW_IF_FAILED(outputStream->WriteAsync(buffer.Get(), &bufferWriteOperation));

            ComPtr<T> strongImageControl(uiElement);
            ComPtr<XamlBuilder> strongThis(this);
            THROW_IF_FAILED(bufferWriteOperation->put_Completed(
                Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<UINT32, UINT32>>>(
                    [strongThis, this, bitmapSource, randomAccessStream, strongImageControl, isAutoSize, parentElement, imageContainer, isVisible](
                        IAsyncOperationWithProgress<UINT32, UINT32>* /*operation*/, AsyncStatus /*status*/) -> HRESULT {
                        randomAccessStream->Seek(0);
                        RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                        ComPtr<IImageSource> imageSource;
                        RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                        SetImageSource(strongImageControl.Get(), imageSource.Get());

                        if (isAutoSize)
                        {
                            SetAutoSize(strongImageControl.Get(), parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                        }

                        return S_OK;
                    })
                    .Get()));

            m_writeAsyncOperations.push_back(bufferWriteOperation);
            *mustHideElement = false;
            return;
        }

        // Otherwise, no resolver...
        if ((m_enableXamlImageHandling) || (m_listeners.size() == 0))
        {
            // If we've been explicitly told to let Xaml handle the image loading, or there are
            // no listeners waiting on the image load callbacks, use Xaml to load the images
            ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
            THROW_IF_FAILED(bitmapImage->put_UriSource(imageUrl));

            ComPtr<IImageSource> bitmapImageSource;
            THROW_IF_FAILED(bitmapImage.As(&bitmapImageSource));
            SetImageSource(uiElement, bitmapImageSource.Get(), stretch);

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
    void XamlBuilder::PopulateImageFromUrlAsync(_In_ IUriRuntimeClass* imageUrl, _In_ T* imageControl)
    {
        // Create the HttpClient to load the image stream
        ComPtr<IHttpBaseProtocolFilter> httpBaseProtocolFilter = XamlHelpers::CreateXamlClass<IHttpBaseProtocolFilter>(
            HStringReference(RuntimeClass_Windows_Web_Http_Filters_HttpBaseProtocolFilter));
        THROW_IF_FAILED(httpBaseProtocolFilter->put_AllowUI(false));
        ComPtr<IHttpFilter> httpFilter;
        THROW_IF_FAILED(httpBaseProtocolFilter.As(&httpFilter));
        ComPtr<IHttpClient> httpClient;
        ComPtr<IHttpClientFactory> httpClientFactory;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Web_Http_HttpClient).Get(),
                                             httpClientFactory.ReleaseAndGetAddressOf()));
        THROW_IF_FAILED(httpClientFactory->Create(httpFilter.Get(), httpClient.ReleaseAndGetAddressOf()));

        // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
        // the tracker to subscribe to the ImageLoaded/Failed events
        ComPtr<IBitmapImage> bitmapImage =
            XamlHelpers::CreateXamlClass<IBitmapImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
        m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
        THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_None));
        ComPtr<IBitmapSource> bitmapSource;
        bitmapImage.As(&bitmapSource);
        ComPtr<IAsyncOperationWithProgress<IInputStream*, HttpProgress>> getStreamOperation;
        THROW_IF_FAILED(httpClient->GetInputStreamAsync(imageUrl, &getStreamOperation));

        ComPtr<T> strongImageControl(imageControl);
        ComPtr<XamlBuilder> strongThis(this);
        THROW_IF_FAILED(getStreamOperation->put_Completed(
            Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<IInputStream*, HttpProgress>>>(
                [strongThis, this, bitmapSource, strongImageControl, bitmapImage](
                    IAsyncOperationWithProgress<IInputStream*, HttpProgress>* operation, AsyncStatus status) -> HRESULT {
                    if (status == AsyncStatus::Completed)
                    {
                        // Load the image stream into an in memory random access stream, which is what
                        // SetSource needs
                        ComPtr<IInputStream> imageStream;
                        RETURN_IF_FAILED(operation->GetResults(&imageStream));
                        ComPtr<IRandomAccessStream> randomAccessStream = XamlHelpers::CreateXamlClass<IRandomAccessStream>(
                            HStringReference(RuntimeClass_Windows_Storage_Streams_InMemoryRandomAccessStream));
                        ComPtr<IOutputStream> outputStream;
                        RETURN_IF_FAILED(randomAccessStream.As(&outputStream));
                        ComPtr<IAsyncOperationWithProgress<UINT64, UINT64>> copyStreamOperation;
                        RETURN_IF_FAILED(m_randomAccessStreamStatics->CopyAsync(imageStream.Get(), outputStream.Get(), &copyStreamOperation));

                        m_copyStreamOperations.push_back(copyStreamOperation);
                        return copyStreamOperation->put_Completed(
                            Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<UINT64, UINT64>>>(
                                [strongThis, this, bitmapSource, randomAccessStream, strongImageControl](
                                    IAsyncOperationWithProgress<UINT64, UINT64>* /*operation*/, AsyncStatus /*status*/) -> HRESULT {
                                    randomAccessStream->Seek(0);
                                    RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                                    ComPtr<IImageSource> imageSource;
                                    RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                                    SetImageSource(strongImageControl.Get(), imageSource.Get());
                                    return S_OK;
                                })
                                .Get());
                    }
                    else
                    {
                        m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                        return S_OK;
                    }
                })
                .Get()));
        m_getStreamOperations.push_back(getStreamOperation);
    }

    template<typename T>
    void XamlBuilder::SetImageSource(_In_ T* destination, _In_ IImageSource* imageSource, ABI::Windows::UI::Xaml::Media::Stretch /*stretch*/)
    {
        THROW_IF_FAILED(destination->put_Source(imageSource));
    };

    template<>
    void XamlBuilder::SetImageSource<IEllipse>(_In_ IEllipse* destination,
                                               _In_ IImageSource* imageSource,
                                               ABI::Windows::UI::Xaml::Media::Stretch stretch)
    {
        ComPtr<IImageBrush> imageBrush =
            XamlHelpers::CreateXamlClass<IImageBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_ImageBrush));
        THROW_IF_FAILED(imageBrush->put_ImageSource(imageSource));

        ComPtr<ITileBrush> tileBrush;
        THROW_IF_FAILED(imageBrush.As(&tileBrush));
        THROW_IF_FAILED(tileBrush->put_Stretch(stretch));

        ComPtr<IBrush> brush;
        THROW_IF_FAILED(imageBrush.As(&brush));

        ComPtr<IShape> ellipseAsShape;
        ComPtr<IEllipse> ellipse(destination);
        THROW_IF_FAILED(ellipse.As(&ellipseAsShape));

        THROW_IF_FAILED(ellipseAsShape->put_Fill(brush.Get()));
    };

    template<>
    void XamlBuilder::SetAutoSize<IEllipse>(IEllipse* destination, IInspectable* parentElement, IInspectable* imageContainer, bool isVisible, bool imageFiresOpenEvent)
    {
        // Check if the image source fits in the parent container, if so, set the framework element's size to match the original image.
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            ComPtr<IInspectable> ellipseShape(imageContainer);
            ComPtr<IShape> ellipseAsShape;
            THROW_IF_FAILED(ellipseShape.As(&ellipseAsShape));

            ComPtr<IBrush> ellipseBrush;
            THROW_IF_FAILED(ellipseAsShape->get_Fill(&ellipseBrush));
            ComPtr<IImageBrush> brushAsImageBrush;
            THROW_IF_FAILED(ellipseBrush.As(&brushAsImageBrush));

            ComPtr<IEllipse> ellipse(destination);

            ComPtr<IUIElement> ellipseAsUIElement;
            THROW_IF_FAILED(ellipse.As(&ellipseAsUIElement));

            ComPtr<IFrameworkElement> ellipseAsFrameworkElement;
            THROW_IF_FAILED(ellipse.As(&ellipseAsFrameworkElement));

            ComPtr<IImageSource> imageSource;
            THROW_IF_FAILED(brushAsImageBrush->get_ImageSource(&imageSource));
            ComPtr<IBitmapSource> imageSourceAsBitmap;
            THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Ellipse while the image loads, so that resizing is not noticeable
                THROW_IF_FAILED(ellipseAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));
                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                EventRegistrationToken eventToken;
                ComPtr<IInspectable> localParentElement(parentElement);

                // Take weak references to the ellipse and parent to avoid circular references between this lambda and
                // its parents (Parent->Ellipse->ImageBrush->Lambda->(Parent and Ellipse))
                WeakRef weakParent;
                THROW_IF_FAILED(localParentElement.AsWeak(&weakParent));

                WeakRef weakEllipse;
                THROW_IF_FAILED(ellipseAsUIElement.AsWeak(&weakEllipse));
                THROW_IF_FAILED(brushAsImageBrush->add_ImageOpened(
                    Callback<IRoutedEventHandler>([weakEllipse, imageSourceAsBitmap, weakParent, isVisible](
                                                      IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                        if (isVisible)
                        {
                            ComPtr<IFrameworkElement> lambdaEllipseAsFrameworkElement;
                            RETURN_IF_FAILED(weakEllipse.As(&lambdaEllipseAsFrameworkElement));

                            ComPtr<IInspectable> lambdaParentElement;
                            RETURN_IF_FAILED(weakParent.As(&lambdaParentElement));

                            if (lambdaEllipseAsFrameworkElement && lambdaParentElement)
                            {
                                RETURN_IF_FAILED(XamlHelpers::SetAutoImageSize(lambdaEllipseAsFrameworkElement.Get(),
                                                                               lambdaParentElement.Get(),
                                                                               imageSourceAsBitmap.Get(),
                                                                               isVisible));
                            }
                        }
                        return S_OK;
                    }).Get(),
                    &eventToken));
            }
            else
            {
                XamlHelpers::SetAutoImageSize(ellipseAsFrameworkElement.Get(), parentElement, imageSourceAsBitmap.Get(), isVisible);
            }
        }
    }

    template<typename T>
    void XamlBuilder::SetAutoSize(T* destination, IInspectable* parentElement, IInspectable* /* imageContainer */, bool isVisible, bool imageFiresOpenEvent)
    {
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            ComPtr<IImage> xamlImage(destination);
            ComPtr<IFrameworkElement> imageAsFrameworkElement;
            THROW_IF_FAILED(xamlImage.As(&imageAsFrameworkElement));
            ComPtr<IImageSource> imageSource;
            THROW_IF_FAILED(xamlImage->get_Source(&imageSource));
            ComPtr<IBitmapSource> imageSourceAsBitmap;
            THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));

            ComPtr<IUIElement> imageAsUIElement;
            THROW_IF_FAILED(xamlImage.As(&imageAsUIElement));

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Image control while the image loads, so that resizing is not noticeable
                THROW_IF_FAILED(imageAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                ComPtr<IInspectable> localParentElement(parentElement);

                // Take weak references to the image and parent to avoid circular references between this lambda and
                // its parents (Parent->Image->Lambda->(Parent and Image))
                WeakRef weakParent;
                THROW_IF_FAILED(localParentElement.AsWeak(&weakParent));

                WeakRef weakImage;
                THROW_IF_FAILED(imageAsFrameworkElement.AsWeak(&weakImage));
                EventRegistrationToken eventToken;
                THROW_IF_FAILED(xamlImage->add_ImageOpened(
                    Callback<IRoutedEventHandler>([weakImage, weakParent, imageSourceAsBitmap, isVisible](IInspectable* /*sender*/, IRoutedEventArgs *
                                                                                                          /*args*/) -> HRESULT {
                        ComPtr<IFrameworkElement> lambdaImageAsFrameworkElement;
                        RETURN_IF_FAILED(weakImage.As(&lambdaImageAsFrameworkElement));

                        ComPtr<IInspectable> lambdaParentElement;
                        RETURN_IF_FAILED(weakParent.As(&lambdaParentElement));

                        if (lambdaImageAsFrameworkElement && lambdaParentElement)
                        {
                            RETURN_IF_FAILED(XamlHelpers::SetAutoImageSize(lambdaImageAsFrameworkElement.Get(),
                                                                           lambdaParentElement.Get(),
                                                                           imageSourceAsBitmap.Get(),
                                                                           isVisible));
                        }
                        return S_OK;
                    }).Get(),
                    &eventToken));
            }
            else
            {
                XamlHelpers::SetAutoImageSize(imageAsFrameworkElement.Get(), parentElement, imageSourceAsBitmap.Get(), isVisible);
            }
        }
    }
}
