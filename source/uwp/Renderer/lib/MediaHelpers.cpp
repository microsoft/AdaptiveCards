#include "pch.h"
#include "XamlHelpers.h"
#include "XamlBuilder.h"
#include "AdaptiveImage.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace AdaptiveNamespace;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;

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
        // TODO: Load default poster from host config
        *posterImage = nullptr;
        return;
    }

    ComPtr<IAdaptiveImage> adaptiveImage;
    THROW_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveImage>(&adaptiveImage));
    THROW_IF_FAILED(adaptiveImage->put_Url(posterString.Get()));

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

void AddPlayButtonIconToImageInRelativePanel(
    IPanel * mediaPanel,
    IFrameworkElement * posterImage,
    IAdaptiveRenderArgs* renderArgs,
    IAdaptiveHostConfig * hostConfig,
    ABI::AdaptiveNamespace::ForegroundColor color,
    DOUBLE scale)
{
    // Create a play symbol icon
    ComPtr<ISymbolIcon> playIcon = XamlHelpers::CreateXamlClass<ISymbolIcon>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_SymbolIcon));
    THROW_IF_FAILED(playIcon->put_Symbol(Symbol::Symbol_Play));

    // Set the color
    ComPtr<IIconElement> playIconAsIconElement;
    THROW_IF_FAILED(playIcon.As(&playIconAsIconElement));

    ABI::AdaptiveNamespace::ContainerStyle containerStyle;
    THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

    ABI::Windows::UI::Color brushColor;
    THROW_IF_FAILED(GetColorFromAdaptiveColor(hostConfig, color, containerStyle, false, &brushColor));

    ComPtr<IBrush> brush = XamlBuilder::GetSolidColorBrush(brushColor);
    THROW_IF_FAILED(playIconAsIconElement->put_Foreground(brush.Get()));

    // Put it in a viewbox so that it can scale with the image
    ComPtr<IUIElement> playIconAsUIElement;
    THROW_IF_FAILED(playIcon.As(&playIconAsUIElement));

    ComPtr<IViewbox> playIconViewbox = XamlHelpers::CreateXamlClass<IViewbox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Viewbox));
    THROW_IF_FAILED(playIconViewbox->put_Child(playIconAsUIElement.Get()));

    // Set the viewbox to be centered on the image in the relative panel
    ComPtr<IRelativePanelStatics> relativePanelStatics;
    THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RelativePanel).Get(), &relativePanelStatics));
    ComPtr<IUIElement> playIconViewboxAsUIElement;
    THROW_IF_FAILED(playIconViewbox.As(&playIconViewboxAsUIElement));
    THROW_IF_FAILED(relativePanelStatics->SetAlignHorizontalCenterWith(playIconViewboxAsUIElement.Get(), posterImage));
    THROW_IF_FAILED(relativePanelStatics->SetAlignVerticalCenterWith(playIconViewboxAsUIElement.Get(), posterImage));

    XamlHelpers::AppendXamlElementToPanel(playIconViewbox.Get(), mediaPanel);

    // Get a strong reference to the poster image to pass to the lambda
    ComPtr<IFrameworkElement> localPosterImage{ posterImage };

    // Add a handler to size changed on the image so that the play button scales with the image
    EventRegistrationToken sizeChangedToken;
    ComPtr<IFrameworkElement> playIconViewboxAsFrameworkElement;
    THROW_IF_FAILED(playIconViewbox.As(&playIconViewboxAsFrameworkElement));
    posterImage->add_SizeChanged(Callback<ISizeChangedEventHandler>([playIconViewboxAsFrameworkElement, localPosterImage, scale](IInspectable* /*sender*/, ISizeChangedEventArgs* /*args*/) -> HRESULT
    {
        DOUBLE imageHeight, imageWidth;
        RETURN_IF_FAILED(localPosterImage->get_ActualHeight(&imageHeight));
        RETURN_IF_FAILED(localPosterImage->get_ActualWidth(&imageWidth));

        RETURN_IF_FAILED(playIconViewboxAsFrameworkElement->put_Height(imageHeight * scale));
        RETURN_IF_FAILED(playIconViewboxAsFrameworkElement->put_Width(imageWidth * scale));

        return S_OK;
    }).Get(), &sizeChangedToken);
}

void CreatePosterContainerWithPlayButton(
    IImage* posterImage,
    IAdaptiveRenderArgs* renderArgs,
    IAdaptiveHostConfig * hostConfig,
    IUIElement ** posterContainer)
{
    ComPtr<IRelativePanel> posterRelativePanel = XamlHelpers::CreateXamlClass<IRelativePanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RelativePanel));

    ComPtr<IPanel> mediaPanel;
    THROW_IF_FAILED(posterRelativePanel.As(&mediaPanel));

    // Append the poster image to the panel
    XamlHelpers::AppendXamlElementToPanel(posterImage, mediaPanel.Get());

    ComPtr<IImage> localPosterImage{ posterImage };
    ComPtr<IFrameworkElement> posterImageAsFrameworkElement;
    localPosterImage.As(&posterImageAsFrameworkElement);

    // Add the play button. Draw slightly smaller and larger versions of the icon in the light 
    // color. This will create a dark button with a light outline so it shows up on all poster image colors.
    // TODO: Handle custom play button from host config
    AddPlayButtonIconToImageInRelativePanel(mediaPanel.Get(), posterImageAsFrameworkElement.Get(), renderArgs, hostConfig, ABI::AdaptiveNamespace::ForegroundColor::Light, .25);
    AddPlayButtonIconToImageInRelativePanel(mediaPanel.Get(), posterImageAsFrameworkElement.Get(), renderArgs, hostConfig, ABI::AdaptiveNamespace::ForegroundColor::Light, .35);
    AddPlayButtonIconToImageInRelativePanel(mediaPanel.Get(), posterImageAsFrameworkElement.Get(), renderArgs, hostConfig, ABI::AdaptiveNamespace::ForegroundColor::Dark, .3);

    ComPtr<IUIElement> posterRelativePanelAsUIElement;
    THROW_IF_FAILED(posterRelativePanel.As(&posterRelativePanelAsUIElement));
    THROW_IF_FAILED(posterRelativePanelAsUIElement.CopyTo(posterContainer));
}

void GetMediaSource(
    IAdaptiveHostConfig* hostConfig,
    IAdaptiveMedia* adaptiveMedia,
    IUriRuntimeClass** mediaSourceUrl)
{
    LPWSTR supportedMimeTypes[] =
    {
        L"video/mp4",
        L"audio/mp4",
        L"audio/mpeg",
    };

    ComPtr<IVector<IAdaptiveMediaSource*>> sources;
    THROW_IF_FAILED(adaptiveMedia->get_Sources(&sources));

    ComPtr<IIterable<IAdaptiveMediaSource*>> sourcesIterable;
    THROW_IF_FAILED(sources.As<IIterable<IAdaptiveMediaSource*>>(&sourcesIterable));

    boolean hasCurrent;
    ComPtr<IIterator<IAdaptiveMediaSource*>> sourceIterator;
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

            if (isSupported)
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
    }
}