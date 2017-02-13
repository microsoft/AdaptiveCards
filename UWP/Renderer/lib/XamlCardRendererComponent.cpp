#include "pch.h"
#include "XamlCardRendererComponent.h"

#include <windows.foundation.collections.h>
#include "XamlBuilder.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;

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
        IUIElement** root) try
    {
        *root = nullptr;

        if (adaptiveCard)
        {
            XamlBuilder builder;
            ComPtr<IUIElement> xamlTreeRoot;
            builder.BuildXamlTreeFromAdaptiveCard(adaptiveCard, &xamlTreeRoot);
            RETURN_IF_FAILED(xamlTreeRoot.CopyTo(root));
        }
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsImage(
        IAdaptiveCard* /*adaptiveCard*/,
        IAsyncOperation<ImageRenderResult*>** result)
    {
        *result = nullptr;
        return S_OK;
    }
}}
