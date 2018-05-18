#include "pch.h"
#include "AdaptiveCardRendererComponent.h"

#include "AdaptiveCard.h"
#include "AdaptiveCardResourceResolvers.h"
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
#include "DefaultResourceDictionary.h"
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"
#include "XamlHelpers.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include <windows.ui.xaml.markup.h>

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage::Streams;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Core;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

AdaptiveNamespaceStart

    HRESULT AdaptiveCardRenderer::RuntimeClassInitialize()
    {
        m_xamlBuilder = std::make_shared<XamlBuilder>();
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveElementRendererRegistration>(&m_elementRendererRegistration));
        RETURN_IF_FAILED(RegisterDefaultElementRenderers());
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&m_hostConfig));
        InitializeDefaultResourceDictionary();
        return MakeAndInitialize<AdaptiveCardResourceResolvers>(&m_resourceResolvers);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::put_OverrideStyles(ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary)
    {
        m_overrideDictionary = overrideDictionary;
        return SetMergedDictionary();
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary)
    {
        return m_overrideDictionary.CopyTo(overrideDictionary);
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
        ComPtr<::AdaptiveNamespace::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::RenderedAdaptiveCard>(&renderedCard));
        renderedCard->SetOriginatingCard(adaptiveCard);

        if (adaptiveCard)
        {
            ComPtr<IFrameworkElement> xamlTreeRoot;

            if (m_explicitDimensions)
            {
                RETURN_IF_FAILED(m_xamlBuilder->SetFixedDimensions(m_desiredWidth, m_desiredHeight));
            }

            ComPtr<AdaptiveRenderContext> renderContext;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderContext>(
                &renderContext,
                m_hostConfig.Get(),
                m_elementRendererRegistration.Get(),
                m_resourceResolvers.Get(),
                m_mergedResourceDictionary.Get(),
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
                RETURN_IF_FAILED(renderContext->AddError(
                    ABI::AdaptiveNamespace::ErrorStatusCode::RenderFailed,
                    HStringReference(L"An unrecoverable error was encountered while rendering the card").Get()));
                renderedCard->SetFrameworkElement(nullptr);
            }
        }
        *result = renderedCard.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RenderCardAsXamlAsync(
        IAdaptiveCard* adaptiveCard,
        IAsyncOperation<ABI::AdaptiveNamespace::RenderedAdaptiveCard*>** result)
    {
        *result = Make<RenderCardAsXamlAsyncOperation>(adaptiveCard, this).Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RenderAdaptiveCardFromJsonString(
        HSTRING adaptiveJson,
        IRenderedAdaptiveCard** result)
    {
        ComPtr<::AdaptiveNamespace::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::RenderedAdaptiveCard>(&renderedCard));

        ComPtr<IAdaptiveCardParseResult> adaptiveCardParseResult;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCardParseResult));
        ComPtr<IAdaptiveCard> parsedCard;
        RETURN_IF_FAILED(adaptiveCardParseResult->get_AdaptiveCard(&parsedCard));
        if (parsedCard == nullptr)
        {            
            ComPtr<IVector<IAdaptiveError*>> renderResultErrors;
            RETURN_IF_FAILED(renderedCard->get_Errors(&renderResultErrors));
            ComPtr<IVector<IAdaptiveError*>> parseErrors;
            RETURN_IF_FAILED(adaptiveCardParseResult->get_Errors(&parseErrors));
            XamlHelpers::IterateOverVector<IAdaptiveError>(parseErrors.Get(), [&](IAdaptiveError* error)
            {
                ComPtr<IAdaptiveError> localError(error);
                return renderResultErrors->Append(localError.Get());
            });
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
        HString adaptiveJsonAsHstring;
        RETURN_IF_FAILED(JsonObjectToHString(adaptiveJson, adaptiveJsonAsHstring.GetAddressOf()));
        return RenderAdaptiveCardFromJsonString(adaptiveJsonAsHstring.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::RenderAdaptiveJsonAsXamlAsync(
        HSTRING adaptiveJson,
        IAsyncOperation<ABI::AdaptiveNamespace::RenderedAdaptiveCard*>** result)
    {
        ComPtr<IAdaptiveCardParseResult> adaptiveCardParseResult;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCardParseResult));

        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(adaptiveCardParseResult->get_AdaptiveCard(&adaptiveCard));
        return RenderCardAsXamlAsync(adaptiveCard.Get(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardRenderer::CreateAdaptiveCardFromJsonString(HSTRING adaptiveJson, ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult)
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
        return m_resourceResolvers.CopyTo(value);
    }

    ComPtr<IResourceDictionary> AdaptiveCardRenderer::GetMergedDictionary()
    {
        return m_mergedResourceDictionary;
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
        return m_elementRendererRegistration.CopyTo(value);
    }

    void AdaptiveCardRenderer::InitializeDefaultResourceDictionary()
    {
        ComPtr<IXamlReaderStatics> xamlReaderStatics;
        THROW_IF_FAILED(RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Markup_XamlReader).Get(),
            __uuidof(IXamlReaderStatics), reinterpret_cast<void**>(xamlReaderStatics.GetAddressOf())));

        ComPtr<IInspectable> resourceDictionaryInspectable;
        THROW_IF_FAILED(xamlReaderStatics->Load(HStringReference(c_defaultResourceDictionary).Get(), &resourceDictionaryInspectable));
        ComPtr<IResourceDictionary> resourceDictionary;
        THROW_IF_FAILED(resourceDictionaryInspectable.As(&resourceDictionary));

        m_mergedResourceDictionary = resourceDictionary;
        m_defaultResourceDictionary = resourceDictionary;
    }

    HRESULT AdaptiveCardRenderer::SetMergedDictionary()
    {
        if (m_overrideDictionary != nullptr)
        {
            m_mergedResourceDictionary = m_overrideDictionary;
            ComPtr<IVector<ResourceDictionary*>> mergedDictionaries;
            RETURN_IF_FAILED(m_mergedResourceDictionary->get_MergedDictionaries(&mergedDictionaries));
            RETURN_IF_FAILED(mergedDictionaries->Append(m_defaultResourceDictionary.Get()));
        }
        return S_OK;
    }

    HRESULT AdaptiveCardRenderer::RegisterDefaultElementRenderers()
    {
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.ChoiceSet").Get(), Make<AdaptiveChoiceSetInputRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Column").Get(), Make<AdaptiveColumnRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"ColumnSet").Get(), Make<AdaptiveColumnSetRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Container").Get(), Make<AdaptiveContainerRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Date").Get(), Make<AdaptiveDateInputRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"FactSet").Get(), Make<AdaptiveFactSetRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Image").Get(), Make<AdaptiveImageRenderer>(m_xamlBuilder).Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"ImageSet").Get(), Make<AdaptiveImageSetRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Number").Get(), Make<AdaptiveNumberInputRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"TextBlock").Get(), Make<AdaptiveTextBlockRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Text").Get(), Make<AdaptiveTextInputRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Time").Get(), Make<AdaptiveTimeInputRenderer>().Get()));
        RETURN_IF_FAILED(m_elementRendererRegistration->Set(HStringReference(L"Input.Toggle").Get(), Make<AdaptiveToggleInputRenderer>().Get()));
        return S_OK;
    }

    std::shared_ptr<XamlBuilder> AdaptiveCardRenderer::GetXamlBuilder()
    {
        return m_xamlBuilder;
    }
AdaptiveNamespaceEnd
