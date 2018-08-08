#include "pch.h"
#include "XamlHelpers.h"
#include "XamlBuilder.h"
#include "AdaptiveImage.h"
#include "AdaptiveCardGetResourceStreamArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace AdaptiveNamespace;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::Storage::Streams;

const DOUBLE c_playIconSize = 30;
const DOUBLE c_playIconCornerRadius = 5;
const DOUBLE c_playIconOpacity = .5;
const DOUBLE c_audioHeight = 100;

void GetMediaPosterAsImage(
    IAdaptiveRenderContext* renderContext,
    IAdaptiveRenderArgs* renderArgs,
    IAdaptiveMedia * adaptiveMedia,
    IImage ** posterImage)
{
    HString posterString;
    THROW_IF_FAILED(adaptiveMedia->get_Poster(posterString.GetAddressOf()));

    if (posterString == nullptr)
    {
        // If the media element doesn't include a poster, use the default from the host config
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveMediaConfig> mediaConfig;
        THROW_IF_FAILED(hostConfig->get_Media(&mediaConfig));

        THROW_IF_FAILED(mediaConfig->get_DefaultPoster(posterString.GetAddressOf()));

        if (posterString == nullptr)
        {
            *posterImage = nullptr;
            return;
        }
    }

    ComPtr<IAdaptiveImage> adaptiveImage;
    THROW_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveImage>(&adaptiveImage));
    THROW_IF_FAILED(adaptiveImage->put_Url(posterString.Get()));

    HString altText;
    THROW_IF_FAILED(adaptiveMedia->get_AltText(altText.GetAddressOf()));
    THROW_IF_FAILED(adaptiveImage->put_AltText(altText.Get()));

    ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
    THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
    ComPtr<IAdaptiveElementRenderer> imageRenderer;
    THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));

    ComPtr<IAdaptiveCardElement> posterAdaptiveElement;
    THROW_IF_FAILED(adaptiveImage.As(&posterAdaptiveElement));

    ComPtr<IUIElement> posterUiElement;
    THROW_IF_FAILED(imageRenderer->Render(posterAdaptiveElement.Get(), renderContext, renderArgs, &posterUiElement));

    ComPtr<IImage> posterAsImage;
    THROW_IF_FAILED(posterUiElement.As(&posterAsImage));
    THROW_IF_FAILED(posterAsImage.CopyTo(posterImage));
}

void AddDefaultPlayIcon(
    IPanel * posterPanel,
    IAdaptiveHostConfig * hostConfig,
    IAdaptiveRenderArgs* renderArgs)
{
    // Create a rectangle
    ComPtr<IRectangle> rectangle = XamlHelpers::CreateXamlClass<IRectangle>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle));

    // Set the size
    ComPtr<IFrameworkElement> rectangleAsFrameworkElement;
    THROW_IF_FAILED(rectangle.As(&rectangleAsFrameworkElement));
    THROW_IF_FAILED(rectangleAsFrameworkElement->put_Height(c_playIconSize));
    THROW_IF_FAILED(rectangleAsFrameworkElement->put_Width(c_playIconSize));

    // Round the corners
    THROW_IF_FAILED(rectangle->put_RadiusX(c_playIconCornerRadius));
    THROW_IF_FAILED(rectangle->put_RadiusY(c_playIconCornerRadius));

    // Set it's fill and opacity
    ComPtr<IShape> rectangleAsShape;
    THROW_IF_FAILED(rectangle.As(&rectangleAsShape));

    ABI::Windows::UI::Color whiteBrushColor{ 0xFF, 0xFF, 0xFF, 0xFF };
    ComPtr<IBrush> rectangleBrush = XamlBuilder::GetSolidColorBrush(whiteBrushColor);
    THROW_IF_FAILED(rectangleAsShape->put_Fill(rectangleBrush.Get()));

    ComPtr<IUIElement> rectangleAsUIElement;
    THROW_IF_FAILED(rectangle.As(&rectangleAsUIElement));
    THROW_IF_FAILED(rectangleAsUIElement->put_Opacity(c_playIconOpacity));

    // Outline it in the Dark color
    ABI::AdaptiveNamespace::ContainerStyle containerStyle;
    THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

    ComPtr<IColorsStatics> colorsStatics;
    THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Colors).Get(), &colorsStatics));

    ABI::Windows::UI::Color darkBrushColor;
    THROW_IF_FAILED(GetColorFromAdaptiveColor(hostConfig, ForegroundColor_Dark, containerStyle, false, &darkBrushColor));

    ComPtr<IBrush> darkBrush = XamlBuilder::GetSolidColorBrush(darkBrushColor);
    rectangleAsShape->put_Stroke(darkBrush.Get());

    // Create a play symbol icon
    ComPtr<ISymbolIcon> playIcon = XamlHelpers::CreateXamlClass<ISymbolIcon>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_SymbolIcon));
    THROW_IF_FAILED(playIcon->put_Symbol(Symbol::Symbol_Play));

    // Set it's color
    ComPtr<IIconElement> playIconAsIconElement;
    THROW_IF_FAILED(playIcon.As(&playIconAsIconElement));
    THROW_IF_FAILED(playIconAsIconElement->put_Foreground(darkBrush.Get()));

    // Put the rectangle and the play icon on the panel and center them
    ComPtr<IRelativePanelStatics> relativePanelStatics;
    THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RelativePanel).Get(), &relativePanelStatics));

    XamlHelpers::AppendXamlElementToPanel(rectangle.Get(), posterPanel);
    THROW_IF_FAILED(relativePanelStatics->SetAlignHorizontalCenterWithPanel(rectangleAsUIElement.Get(), true));
    THROW_IF_FAILED(relativePanelStatics->SetAlignVerticalCenterWithPanel(rectangleAsUIElement.Get(), true));

    ComPtr<IUIElement> playIconAsUIElement;
    THROW_IF_FAILED(playIcon.As(&playIconAsUIElement));
    XamlHelpers::AppendXamlElementToPanel(playIcon.Get(), posterPanel);
    THROW_IF_FAILED(relativePanelStatics->SetAlignHorizontalCenterWithPanel(playIconAsUIElement.Get(), true));
    THROW_IF_FAILED(relativePanelStatics->SetAlignVerticalCenterWithPanel(playIconAsUIElement.Get(), true));
}

void AddCustomPlayIcon(
    IPanel * posterPanel, 
    HSTRING playIconString,
    IAdaptiveRenderContext* renderContext,
    IAdaptiveRenderArgs* renderArgs)
{
    // Render the custom play icon using the image renderer
    ComPtr<IAdaptiveImage> playIconAdaptiveImage;
    THROW_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveImage>(&playIconAdaptiveImage));
    THROW_IF_FAILED(playIconAdaptiveImage->put_Url(playIconString));

    ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
    THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
    ComPtr<IAdaptiveElementRenderer> imageRenderer;
    THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));

    ComPtr<IAdaptiveCardElement> playIconImageAsAdaptiveElement;
    THROW_IF_FAILED(playIconAdaptiveImage.As(&playIconImageAsAdaptiveElement));

    ComPtr<IUIElement> playIconUIElement;
    THROW_IF_FAILED(imageRenderer->Render(playIconImageAsAdaptiveElement.Get(), renderContext, renderArgs, &playIconUIElement));

    ComPtr<IFrameworkElement> playIconAsFrameworkElement;
    THROW_IF_FAILED(playIconUIElement.As(&playIconAsFrameworkElement));
    THROW_IF_FAILED(playIconAsFrameworkElement->put_Height(c_playIconSize));

    // Add it to the panel and center it
    ComPtr<IRelativePanelStatics> relativePanelStatics;
    THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RelativePanel).Get(), &relativePanelStatics));

    XamlHelpers::AppendXamlElementToPanel(playIconUIElement.Get(), posterPanel);
    THROW_IF_FAILED(relativePanelStatics->SetAlignHorizontalCenterWithPanel(playIconUIElement.Get(), true));
    THROW_IF_FAILED(relativePanelStatics->SetAlignVerticalCenterWithPanel(playIconUIElement.Get(), true));
}

void AddPlayIcon(
    IPanel * posterPanel,
    IAdaptiveRenderContext* renderContext,
    IAdaptiveRenderArgs* renderArgs)
{
    ComPtr<IAdaptiveHostConfig> hostConfig;
    THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

    ComPtr<IAdaptiveMediaConfig> mediaConfig;
    THROW_IF_FAILED(hostConfig->get_Media(&mediaConfig));

    HString customPlayIconString;
    THROW_IF_FAILED(mediaConfig->get_PlayButton(customPlayIconString.GetAddressOf()));

    if (customPlayIconString == nullptr)
    {
        AddDefaultPlayIcon(posterPanel, hostConfig.Get(), renderArgs);
    }
    else
    {
        AddCustomPlayIcon(posterPanel, customPlayIconString.Get(), renderContext, renderArgs);
    }
}

void CreatePosterContainerWithPlayButton(
    IImage* posterImage,
    IAdaptiveRenderContext* renderContext,
    IAdaptiveRenderArgs* renderArgs,
    IUIElement ** posterContainer)
{
    ComPtr<IRelativePanel> posterRelativePanel = XamlHelpers::CreateXamlClass<IRelativePanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RelativePanel));

    ComPtr<IPanel> posterPanel;
    THROW_IF_FAILED(posterRelativePanel.As(&posterPanel));

    ComPtr<IFrameworkElement> posterImageAsFrameworkElement;
    if (posterImage != nullptr)
    {
        // Append the poster image to the panel
        XamlHelpers::AppendXamlElementToPanel(posterImage, posterPanel.Get());

        ComPtr<IImage> localPosterImage{ posterImage };
        localPosterImage.As(&posterImageAsFrameworkElement);
    }

    AddPlayIcon(posterPanel.Get(), renderContext, renderArgs);

    ComPtr<IUIElement> posterRelativePanelAsUIElement;
    THROW_IF_FAILED(posterRelativePanel.As(&posterRelativePanelAsUIElement));
    THROW_IF_FAILED(posterRelativePanelAsUIElement.CopyTo(posterContainer));
}

void GetMediaSource(
    IAdaptiveHostConfig* hostConfig,
    IAdaptiveMedia* adaptiveMedia,
    IUriRuntimeClass** mediaSourceUrl,
    HSTRING * mimeType)
{
    LPWSTR supportedMimeTypes[] =
    {
        L"video/mp4",
        L"audio/mp4",
		L"audio/aac",
		L"audio/mpeg",
    };

    ComPtr<IVector<AdaptiveMediaSource*>> sources;
    THROW_IF_FAILED(adaptiveMedia->get_Sources(&sources));

    ComPtr<IIterable<AdaptiveMediaSource*>> sourcesIterable;
    THROW_IF_FAILED(sources.As<IIterable<AdaptiveMediaSource*>>(&sourcesIterable));

    boolean hasCurrent;
    ComPtr<IIterator<AdaptiveMediaSource*>> sourceIterator;
    HRESULT hr = sourcesIterable->First(&sourceIterator);
    THROW_IF_FAILED(sourceIterator->get_HasCurrent(&hasCurrent));

    ComPtr<IAdaptiveMediaSource> selectedSource;
    while (SUCCEEDED(hr) && hasCurrent)
    {
        ComPtr<IAdaptiveMediaSource> currentSource;
        THROW_IF_FAILED(sourceIterator->get_Current(&currentSource));

        HString mimeType;
        THROW_IF_FAILED(currentSource->get_MimeType(mimeType.GetAddressOf()));

        INT32 isSupported;
        for (UINT i = 0; i < ARRAYSIZE(supportedMimeTypes); i++)
        {
            THROW_IF_FAILED(WindowsCompareStringOrdinal(mimeType.Get(), HStringReference(supportedMimeTypes[i]).Get(), &isSupported));

            if (isSupported == 0)
            {
                selectedSource = currentSource;
                break;
            }
        }

        hr = sourceIterator->MoveNext(&hasCurrent);
    }

    if (selectedSource != nullptr)
    {
        HString url;
        THROW_IF_FAILED(selectedSource->get_Url(url.GetAddressOf()));

        ComPtr<IUriRuntimeClass> sourceUrl;
        GetUrlFromString(hostConfig, url.Get(), sourceUrl.GetAddressOf());

        THROW_IF_FAILED(sourceUrl.CopyTo(mediaSourceUrl));
        THROW_IF_FAILED(selectedSource->get_MimeType(mimeType));
    }
}

HRESULT HandleMediaResourceResolverCompleted(
    IAsyncOperation<IRandomAccessStream*>* operation,
    AsyncStatus status,
    IMediaElement* mediaElement,
    HSTRING mimeType)
{
    if (status == AsyncStatus::Completed)
    {
        // Get the random access stream
        ComPtr<IRandomAccessStream> randomAccessStream;
        RETURN_IF_FAILED(operation->GetResults(&randomAccessStream));

        if (randomAccessStream != nullptr)
        {
            RETURN_IF_FAILED(mediaElement->SetSource(randomAccessStream.Get(), mimeType));
        }
    }
    return S_OK;
}

HRESULT HandleMediaClick(
    IAdaptiveRenderContext* renderContext,
    IAdaptiveMedia* adaptiveMedia,
    IMediaElement* mediaElement,
    IUIElement* posterContainer,
    IUriRuntimeClass* mediaSourceUrl,
    HSTRING mimeType,
    IAdaptiveMediaEventInvoker* mediaInvoker)
{
    // When the user clicks: hide the poster, show the media element, open and play the media
    if (mediaElement)
    {
		ComPtr<IMediaElement> localMediaElement{ mediaElement };

		RETURN_IF_FAILED(posterContainer->put_Visibility(Visibility_Collapsed));

        ComPtr<IUIElement> mediaAsUIElement;
        RETURN_IF_FAILED(localMediaElement.As(&mediaAsUIElement));
        RETURN_IF_FAILED(mediaAsUIElement->put_Visibility(Visibility_Visible));

        ComPtr<IAdaptiveCardResourceResolvers> resourceResolvers;
        THROW_IF_FAILED(renderContext->get_ResourceResolvers(&resourceResolvers));

        ComPtr<IAdaptiveCardResourceResolver> resourceResolver;
        if (resourceResolvers != nullptr)
        {
            HString schemeName;
            THROW_IF_FAILED(mediaSourceUrl->get_SchemeName(schemeName.GetAddressOf()));
            THROW_IF_FAILED(resourceResolvers->Get(schemeName.Get(), &resourceResolver));
        }

        if (resourceResolver == nullptr)
        {
            // If there isn't a resource resolver, put the source directly. 
            THROW_IF_FAILED(mediaElement->put_Source(mediaSourceUrl));    
        }
        else
        {
            // Create the arguments to pass to the resolver
            ComPtr<IAdaptiveCardGetResourceStreamArgs> args;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveCardGetResourceStreamArgs>(&args, mediaSourceUrl));

            // Call the resolver to get the media stream
            ComPtr<IAsyncOperation<IRandomAccessStream*>> getResourceStreamOperation;
            RETURN_IF_FAILED(resourceResolver->GetResourceStreamAsync(args.Get(), &getResourceStreamOperation));

            // Take a reference to the mime type string for the lambda
            HSTRING lambdaMimeType;
            WindowsDuplicateString(mimeType, &lambdaMimeType);

            RETURN_IF_FAILED(getResourceStreamOperation->put_Completed(Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationCompletedHandler<IRandomAccessStream*>>>
                ([localMediaElement, lambdaMimeType](IAsyncOperation<IRandomAccessStream*>* operation, AsyncStatus status) -> HRESULT
            {
                // Take ownership of the passed in HSTRING
                HString localMimeType;
                localMimeType.Attach(lambdaMimeType);

                return HandleMediaResourceResolverCompleted(operation, status, localMediaElement.Get(), lambdaMimeType);
            }).Get()));
        }

        EventRegistrationToken mediaOpenedToken;
        THROW_IF_FAILED(mediaElement->add_MediaOpened(Callback<IRoutedEventHandler>([=](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT
        {
            boolean audioOnly;
            RETURN_IF_FAILED(localMediaElement->get_IsAudioOnly(&audioOnly));

            ComPtr<IImageSource> posterSource;
            RETURN_IF_FAILED(localMediaElement->get_PosterSource(&posterSource));

            if (audioOnly && posterSource == nullptr)
            {
                // If this is audio only and there's no poster, set the height so that the 
                // controls are visible.
                ComPtr<IFrameworkElement> mediaAsFrameworkElement;
                RETURN_IF_FAILED(localMediaElement.As(&mediaAsFrameworkElement));
                RETURN_IF_FAILED(mediaAsFrameworkElement->put_Height(c_audioHeight));
            }

            RETURN_IF_FAILED(localMediaElement->Play());
            return S_OK;
        }).Get(), &mediaOpenedToken));
    }
    else
    {
        RETURN_IF_FAILED(mediaInvoker->SendMediaClickedEvent(adaptiveMedia));
    }

    return S_OK;
}