#include "pch.h"
#include "XamlCardRendererComponent.h"

#include "AdaptiveActionRendererRegistration.h"
#include "AdaptiveCard.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveColumnRenderer.h"
#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveDateInputRenderer.h"
#include "AdaptiveElementRendererRegistration.h"
#include "AdaptiveFactSetRenderer.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveImageRenderer.h"
#include "AdaptiveImageSetRenderer.h"
#include "AdaptiveNumberInputRenderer.h"
#include "AdaptiveOpenUrlActionRenderer.h"
#include "AdaptiveRenderContext.h"
#include "AdaptiveShowCardActionRenderer.h"
#include "AdaptiveSubmitActionRenderer.h"
#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveToggleInputRenderer.h"
#include "AsyncOperations.h"
#include "InputItem.h"
#include "RenderedAdaptiveCard.h"
#include "XamlBuilder.h"
#include "XamlCardResourceResolvers.h"
#include "XamlHelpers.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Data::Json;
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
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveElementRendererRegistration>(&m_elementRendererRegistration));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionRendererRegistration>(&m_actionRendererRegistration));
        RETURN_IF_FAILED(RegisterDefaultElementRenderers());
        RETURN_IF_FAILED(RegisterDefaultActionRenderers());
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&m_hostConfig));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderContext>(&m_renderContext,
            m_hostConfig.Get(),
            m_elementRendererRegistration.Get(),
            m_actionRendererRegistration.Get()));
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
    HRESULT  XamlCardRenderer::put_HostConfig(IAdaptiveHostConfig* hostConfig)
    {
        m_hostConfig = hostConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  XamlCardRenderer::get_HostConfig(IAdaptiveHostConfig** hostConfig)
    {
        *hostConfig = m_hostConfig.Get();
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
        HRESULT hr = CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCard);
        if (FAILED(hr))
        {
            HString error;
            RETURN_IF_FAILED(error.Set(L"There was an error creating the card from Json."));
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
    HRESULT XamlCardRenderer::RenderAdaptiveCardFromJson(
            IJsonObject* adaptiveJson,
            IRenderedAdaptiveCard** result)
    {
        HSTRING adaptiveJsonAsHstring;
        RETURN_IF_FAILED(JsonObjectToHString(adaptiveJson, &adaptiveJsonAsHstring));
        return RenderAdaptiveCardFromJsonString(adaptiveJsonAsHstring, result);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RenderAdaptiveJsonAsXamlAsync(
        HSTRING adaptiveJson,
        IAsyncOperation<UIElement*>** result)
    {
        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCard));

        return RenderCardAsXamlAsync(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::CreateAdaptiveCardFromJsonString(HSTRING adaptiveJson, ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** adaptiveCard)
    {
        ComPtr<IAdaptiveCardStatics> adaptiveCardStatics;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardStaticsImpl>(&adaptiveCardStatics));
        return adaptiveCardStatics->FromJsonString(adaptiveJson, adaptiveCard);
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

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::get_ElementRenderers(IAdaptiveElementRendererRegistration **value)
    {
        *value = m_elementRendererRegistration.Get();
        return S_OK;
    }
    _Use_decl_annotations_
    HRESULT XamlCardRenderer::get_ActionRenderers(IAdaptiveActionRendererRegistration **value)
    {
        *value = m_actionRendererRegistration.Get();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RegisterDefaultElementRenderers()
    {
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.ChoiceSet").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveChoiceSetInputRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Column").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveColumnRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"ColumnSet").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveColumnSetRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Container").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveContainerRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Date").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveDateInputRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"FactSet").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveFactSetRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Image").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveImageRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"ImageSet").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveImageSetRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Number").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveNumberInputRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"TextBlock").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveTextBlockRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Text").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveTextInputRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Time").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveTimeInputRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Toggle").Get(), ComPtr<IAdaptiveElementRenderer>(Make<AdaptiveToggleInputRenderer>().Get()).Get()));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardRenderer::RegisterDefaultActionRenderers()
    {
        RETURN_IF_FAILED(m_actionRendererRegistration->Set(HStringReference(L"Action.Submit").Get(), ComPtr<IAdaptiveActionRenderer>(Make<AdaptiveSubmitActionRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_actionRendererRegistration->Set(HStringReference(L"Action.OpenUrl").Get(), ComPtr<IAdaptiveActionRenderer>(Make<AdaptiveOpenUrlActionRenderer>().Get()).Get()));
        RETURN_IF_FAILED(m_actionRendererRegistration->Set(HStringReference(L"Action.ShowCard").Get(), ComPtr<IAdaptiveActionRenderer>(Make<AdaptiveShowCardActionRenderer>().Get()).Get()));
        return S_OK;
    }

}}
