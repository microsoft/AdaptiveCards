#include "pch.h"
#include "XamlCardRendererComponent.h"

#include "AdaptiveCard.h"
#include "AsyncOperations.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlCardResourceResolvers.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"
#include "InputItem.h"
#include "RenderedAdaptiveCard.h"

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
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&m_hostConfig));
        return MakeAndInitialize<XamlCardResourceResolvers>(&m_resourceResolvers);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetRenderOptions(ABI::AdaptiveCards::XamlCardRenderer::RenderOptions /*options*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::SetOverrideStyles(ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary)
    {
        m_overrideDictionary = overrideDictionary;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  XamlCardRenderer::SetHostConfig(IAdaptiveHostConfig* hostConfig)
    {
        m_hostConfig = hostConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  XamlCardRenderer::SetFixedDimensions(_In_ UINT32 desiredWidth, _In_ UINT32 desiredHeight)
    {
        m_explicitDimensions = true;
        m_desiredWidth = desiredWidth;
        m_desiredHeight = desiredHeight;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  XamlCardRenderer::ResetFixedDimensions()
    {
        m_explicitDimensions = false;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveCard(
        IAdaptiveCard* adaptiveCard, 
        IRenderedAdaptiveCard** result)
    {
        ComPtr<::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard>(&renderedCard));
        renderedCard->SetOriginatingCard(adaptiveCard);

        if (adaptiveCard)
        {
            ComPtr<IUIElement> xamlTreeRoot;
            XamlBuilder builder;

            if (m_overrideDictionary != nullptr)
            {
                THROW_IF_FAILED(builder.SetOverrideDictionary(m_overrideDictionary.Get()));
            }

            if (m_hostConfig != nullptr)
            {
                THROW_IF_FAILED(builder.SetHostConfig(m_hostConfig.Get()));
            }

            if (m_explicitDimensions)
            {
                THROW_IF_FAILED(builder.SetFixedDimensions(m_desiredWidth, m_desiredHeight));
            }

            // This path is used for synchronous Xaml card rendering, so we don't want
            // to manually download the image assets and instead just want xaml to do
            // that automatically
            builder.SetEnableXamlImageHandling(true);
            try
            {
                builder.BuildXamlTreeFromAdaptiveCard(adaptiveCard, &xamlTreeRoot, this, renderedCard.Get());
                renderedCard->SetFrameworkElement(xamlTreeRoot.Get());
            }
            catch (...)
            {
                HString error;
                RETURN_IF_FAILED(error.Set(L"There was an error rendering this card"));
                ComPtr<IVector<HSTRING>> errors;
                RETURN_IF_FAILED(renderedCard->get_Errors(&errors));
                errors->Append(error.Detach());
            }
        }
        else
        {
            HString error;
            RETURN_IF_FAILED(error.Set(L"There was an error in the card attempting to being rendered."));
            ComPtr<IVector<HSTRING>> errors;
            RETURN_IF_FAILED(renderedCard->get_Errors(&errors));
            errors->Append(error.Detach());
        }
        *result = renderedCard.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderCardAsXamlAsync(
        IAdaptiveCard* adaptiveCard,
        IAsyncOperation<UIElement*>** result)
    {
        *result = Make<RenderCardAsXamlAsyncOperation>(adaptiveCard, this).Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveCardFromJsonString(
        HSTRING adaptiveJson,
        IRenderedAdaptiveCard** result)
    {
        ComPtr<::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard>(&renderedCard));

        ComPtr<IAdaptiveCard> adaptiveCard;
        HRESULT hr = CreateAdaptiveCardFromJson(adaptiveJson, &adaptiveCard);
        if (FAILED(hr))
        {
            HString error;
            RETURN_IF_FAILED(error.Set(L"There was an error in the card attempting to being rendered."));
            ComPtr<IVector<HSTRING>> errors;
            RETURN_IF_FAILED(renderedCard->get_Errors(&errors));
            errors->Append(error.Detach());
            *result = renderedCard.Detach();
            return S_OK;
        }
        else
        {
            return RenderAdaptiveCard(adaptiveCard.Get(), result);
        }
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
    HRESULT XamlCardRenderer::CreateAdaptiveCardFromJson(HSTRING adaptiveJson, ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** adaptiveCard)
    {
        ComPtr<IAdaptiveCardStatics> adaptiveCardStatics;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardStaticsImpl>(&adaptiveCardStatics));
        RETURN_IF_FAILED(adaptiveCardStatics->CreateCardFromJson(adaptiveJson, adaptiveCard));
        return S_OK;
    }

    IAdaptiveHostConfig* XamlCardRenderer::GetHostConfig()
    {
        return m_hostConfig.Get();
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::get_ResourceResolvers(IXamlCardResourceResolvers** value)
    {
        ComPtr<IXamlCardResourceResolvers> localResourceResolvers(m_resourceResolvers);
        *value = localResourceResolvers.Detach();
        return S_OK;
    }

    ABI::Windows::UI::Xaml::IResourceDictionary* XamlCardRenderer::GetOverrideDictionary()
    {
        return m_overrideDictionary.Get();
    }

    bool XamlCardRenderer::GetFixedDimensions(_Out_ UINT32* width, _Out_ UINT32* height)
    {
        *width = 0;
        *height = 0;

        if (m_explicitDimensions)
        {
            *width = m_desiredWidth;
            *height = m_desiredHeight;
        }

        return m_explicitDimensions;
    }

}}
