#include "pch.h"
#include "XamlCardRendererComponent.h"

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

        // TODO MSFT:10826542 - XamlTileRenderer:Delay rendering completion until images are fully available
        
        //*result = 

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXamlAsync(IAdaptiveCard* adaptiveCard,
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
}}
