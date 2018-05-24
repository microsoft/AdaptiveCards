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

void AddPlayButtonIcon(
    IPanel * mediaPanel)
{
    // Create a play symbol icon
    ComPtr<ISymbolIcon> playIcon = XamlHelpers::CreateXamlClass<ISymbolIcon>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_SymbolIcon));
    THROW_IF_FAILED(playIcon->put_Symbol(Symbol::Symbol_Play));

    ComPtr<IUIElement> playIconAsUIElement;
    playIcon.As(&playIconAsUIElement);

    // Set the icon to be centered in the relative panel
    ComPtr<IRelativePanelStatics> relativePanelStatics;
    THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RelativePanel).Get(), &relativePanelStatics));
    THROW_IF_FAILED(relativePanelStatics->SetAlignHorizontalCenterWithPanel(playIconAsUIElement.Get(), true));
    THROW_IF_FAILED(relativePanelStatics->SetAlignVerticalCenterWithPanel(playIconAsUIElement.Get(), true));

    XamlHelpers::AppendXamlElementToPanel(playIcon.Get(), mediaPanel);
}

void CreatePosterContainerWithPlayButton(
    IImage* posterImage,
    IAdaptiveRenderArgs* /*renderArgs*/,
    IAdaptiveHostConfig * /*hostConfig*/,
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

    // TODO: Handle custom play button from host config
    AddPlayButtonIcon(mediaPanel.Get());

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