#include "pch.h"
#include "AdaptiveCardRendererComponent.h"

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
#include "AdaptiveRenderContext.h"
#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveToggleInputRenderer.h"
#include "AsyncOperations.h"
#include "InputItem.h"
#include "RenderedAdaptiveCard.h"
#include "XamlBuilder.h"
#include "AdaptiveCardResourceResolvers.h"
#include "XamlHelpers.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
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

namespace AdaptiveCards { namespace Uwp
{
    AdaptiveCardRenderer::AdaptiveCardRenderer()
    {
    }

    HRESULT AdaptiveCardRenderer::RuntimeClassInitialize()
    {
        m_xamlBuilder = std::make_shared<XamlBuilder>();
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveElementRendererRegistration>(&m_elementRendererRegistration));
        RETURN_IF_FAILED(RegisterDefaultElementRenderers());
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&m_hostConfig));
        return MakeAndInitialize<AdaptiveCardResourceResolvers>(&m_resourceResolvers);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::SetOverrideStyles(ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary)
    {
        m_overrideDictionary = overrideDictionary;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::put_HostConfig(IAdaptiveHostConfig* hostConfig)
    {
        m_hostConfig = hostConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::get_HostConfig(IAdaptiveHostConfig** hostConfig)
    {
        *hostConfig = m_hostConfig.Get();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::SetFixedDimensions(_In_ UINT32 desiredWidth, _In_ UINT32 desiredHeight)
    {
        m_explicitDimensions = true;
        m_desiredWidth = desiredWidth;
        m_desiredHeight = desiredHeight;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::ResetFixedDimensions()
    {
        m_explicitDimensions = false;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RenderAdaptiveCard(
        IAdaptiveCard* adaptiveCard, 
        IRenderedAdaptiveCard** result)
    {
        ComPtr<::AdaptiveCards::Uwp::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::RenderedAdaptiveCard>(&renderedCard));
        renderedCard->SetOriginatingCard(adaptiveCard);

        if (adaptiveCard)
        {
            ComPtr<IUIElement> xamlTreeRoot;

            if (m_overrideDictionary != nullptr)
            {
                RETURN_IF_FAILED(m_xamlBuilder->SetOverrideDictionary(m_overrideDictionary.Get()));
            }

            if (m_hostConfig != nullptr)
            {
                RETURN_IF_FAILED(m_xamlBuilder->SetHostConfig(m_hostConfig.Get()));
            }

            if (m_explicitDimensions)
            {
                RETURN_IF_FAILED(m_xamlBuilder->SetFixedDimensions(m_desiredWidth, m_desiredHeight));
            }

            ComPtr<AdaptiveRenderContext> renderContext;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderContext>(
                &renderContext,
                m_hostConfig.Get(),
                m_elementRendererRegistration.Get(),
                renderedCard.Get()));

            // This path is used for synchronous Xaml card rendering, so we don't want
            // to manually download the image assets and instead just want xaml to do
            // that automatically
            m_xamlBuilder->SetEnableXamlImageHandling(true);
            try
            {
                m_xamlBuilder->BuildXamlTreeFromAdaptiveCard(adaptiveCard, &xamlTreeRoot, this, renderContext.Get());
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
    HRESULT AdaptiveCardRenderer::RenderCardAsXamlAsync(
        IAdaptiveCard* adaptiveCard,
        IAsyncOperation<UIElement*>** result)
    {
        *result = Make<RenderCardAsXamlAsyncOperation>(adaptiveCard, this).Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RenderAdaptiveCardFromJsonString(
        HSTRING adaptiveJson,
        IRenderedAdaptiveCard** result)
    {
        ComPtr<::AdaptiveCards::Uwp::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::RenderedAdaptiveCard>(&renderedCard));

        ComPtr<IAdaptiveCardParseResult> adaptiveCardParseResult;
        HRESULT hr = CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCardParseResult);
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
            ComPtr<IAdaptiveCard> adaptiveCard;
            RETURN_IF_FAILED(adaptiveCardParseResult->get_AdaptiveCard(&adaptiveCard));

            return RenderAdaptiveCard(adaptiveCard.Get(), result);
        }
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RenderAdaptiveCardFromJson(
            IJsonObject* adaptiveJson,
            IRenderedAdaptiveCard** result)
    {
        HSTRING adaptiveJsonAsHstring;
        RETURN_IF_FAILED(JsonObjectToHString(adaptiveJson, &adaptiveJsonAsHstring));
        return RenderAdaptiveCardFromJsonString(adaptiveJsonAsHstring, result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RenderAdaptiveJsonAsXamlAsync(
        HSTRING adaptiveJson,
        IAsyncOperation<UIElement*>** result)
    {
        ComPtr<IAdaptiveCardParseResult> adaptiveCardParseResult;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCardParseResult));

        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(adaptiveCardParseResult->get_AdaptiveCard(&adaptiveCard));
        return RenderCardAsXamlAsync(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::CreateAdaptiveCardFromJsonString(HSTRING adaptiveJson, ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult** parseResult)
    {
        ComPtr<IAdaptiveCardStatics> adaptiveCardStatics;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardStaticsImpl>(&adaptiveCardStatics));
        return adaptiveCardStatics->FromJsonString(adaptiveJson, parseResult);
    }

    IAdaptiveHostConfig* AdaptiveCardRenderer::GetHostConfig()
    {
        return m_hostConfig.Get();
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::get_ResourceResolvers(IAdaptiveCardResourceResolvers** value)
    {
        ComPtr<IAdaptiveCardResourceResolvers> localResourceResolvers(m_resourceResolvers);
        *value = localResourceResolvers.Detach();
        return S_OK;
    }

    ABI::Windows::UI::Xaml::IResourceDictionary* AdaptiveCardRenderer::GetOverrideDictionary()
    {
        return m_overrideDictionary.Get();
    }

    bool AdaptiveCardRenderer::GetFixedDimensions(_Out_ UINT32* width, _Out_ UINT32* height)
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
    HRESULT AdaptiveCardRenderer::get_ElementRenderers(IAdaptiveElementRendererRegistration **value)
    {
        *value = m_elementRendererRegistration.Get();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RegisterDefaultElementRenderers()
    {
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.ChoiceSet").Get(), Make<AdaptiveChoiceSetInputRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Column").Get(), Make<AdaptiveColumnRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"ColumnSet").Get(), Make<AdaptiveColumnSetRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Container").Get(), Make<AdaptiveContainerRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Date").Get(), Make<AdaptiveDateInputRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"FactSet").Get(), Make<AdaptiveFactSetRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Image").Get(), Make<AdaptiveImageRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"ImageSet").Get(), Make<AdaptiveImageSetRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Number").Get(), Make<AdaptiveNumberInputRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"TextBlock").Get(), Make<AdaptiveTextBlockRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Text").Get(), Make<AdaptiveTextInputRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Time").Get(), Make<AdaptiveTimeInputRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Toggle").Get(), Make<AdaptiveToggleInputRenderer>(m_xamlBuilder).Get()));
        return S_OK;
    }

}}
