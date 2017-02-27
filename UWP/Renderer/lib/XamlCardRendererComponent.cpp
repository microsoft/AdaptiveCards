#include "pch.h"
#include "XamlCardRendererComponent.h"

#include "AdaptiveCard.h"
#include "AsyncOperations.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage::Streams;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Core;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    XamlCardRenderer::XamlCardRenderer()
    {
    }

    HRESULT XamlCardRenderer::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetRenderOptions(ABI::AdaptiveCards::XamlCardRenderer::RenderOptions /*options*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetOverrideStyles(ABI::Windows::UI::Xaml::IResourceDictionary* /*overrideDictionary*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXaml(
        IAdaptiveCard* adaptiveCard, 
        IUIElement** result) try
    {
        *result = nullptr;

        if (adaptiveCard)
        {
            XamlBuilder builder;
            ComPtr<IUIElement> xamlTreeRoot;
            builder.BuildXamlTreeFromAdaptiveCard(adaptiveCard, &xamlTreeRoot);

            *result = xamlTreeRoot.Detach();
        }

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXamlAsync(
        IAdaptiveCard* adaptiveCard,
        IAsyncOperation<UIElement*>** result)
    {
        *result = Make<RenderCardAsXamlAsyncOperation>(adaptiveCard).Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsImageAsync(
        IAdaptiveCard* adaptiveCard,
        IAsyncOperation<ImageRenderResult*>** result)
    {
        *result = Make<RenderCardAsImageAsyncOperation>(adaptiveCard).Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsXaml(
        HSTRING adaptiveJson,
        IUIElement** result)
    {
        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJson(adaptiveJson, &adaptiveCard));

        return RenderCardAsXaml(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsXamlAsync(
        HSTRING adaptiveJson,
        IAsyncOperation<UIElement*>** result)
    {
        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJson(adaptiveJson, &adaptiveCard));

        return RenderCardAsXamlAsync(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsImageAsync(HSTRING adaptiveJson,
        IAsyncOperation<ImageRenderResult*>** result)
    {
        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJson(adaptiveJson, &adaptiveCard));

        return RenderCardAsImageAsync(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::CreateAdaptiveCardFromJson(HSTRING adaptiveJson, ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** adaptiveCard)
    {
        ComPtr<IAdaptiveCardStatics> adaptiveCardStatics;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardStaticsImpl>(&adaptiveCardStatics));
        RETURN_IF_FAILED(adaptiveCardStatics->CreateCardFromJson(adaptiveJson, adaptiveCard));
        return S_OK;
    }

}}