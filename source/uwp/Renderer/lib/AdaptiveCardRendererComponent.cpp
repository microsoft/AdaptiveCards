// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardRendererComponent.h"

#include "AdaptiveCard.h"
#include "AdaptiveCardResourceResolvers.h"
#include "AdaptiveActionRendererRegistration.h"
#include "AdaptiveActionSetRenderer.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveColumnRenderer.h"
#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveDateInputRenderer.h"
#include "AdaptiveElementRendererRegistration.h"
#include "AdaptiveFactSetRenderer.h"
#include "AdaptiveFeatureRegistration.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveImageRenderer.h"
#include "AdaptiveImageSetRenderer.h"
#include "AdaptiveMediaRenderer.h"
#include "AdaptiveNumberInputRenderer.h"
#include "AdaptiveOpenUrlActionRenderer.h"
#include "AdaptiveRenderContext.h"
#include "AdaptiveShowCardActionRenderer.h"
#include "AdaptiveSubmitActionRenderer.h"
#include "AdaptiveRichTextBlockRenderer.h"
#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveToggleVisibilityActionRenderer.h"
#include "AdaptiveToggleInputRenderer.h"
#include "AsyncOperations.h"
#include "DefaultResourceDictionary.h"
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"

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

namespace AdaptiveNamespace
{
    HRESULT AdaptiveCardRenderer::RuntimeClassInitialize() noexcept
    try
    {
        RETURN_IF_FAILED(MakeAndInitialize<XamlBuilder>(&m_xamlBuilder));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveElementRendererRegistration>(&m_elementRendererRegistration));
        RETURN_IF_FAILED(RegisterDefaultElementRenderers(m_elementRendererRegistration, m_xamlBuilder));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionRendererRegistration>(&m_actionRendererRegistration));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFeatureRegistration>(&m_featureRegistration));
        RETURN_IF_FAILED(RegisterDefaultActionRenderers(m_actionRendererRegistration));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&m_hostConfig));
        InitializeDefaultResourceDictionary();
        UpdateActionSentimentResourceDictionary();
        return MakeAndInitialize<AdaptiveCardResourceResolvers>(&m_resourceResolvers);
    }
    CATCH_RETURN;

    HRESULT AdaptiveCardRenderer::put_OverrideStyles(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary)
    {
        m_overrideDictionary = overrideDictionary;
        return SetMergedDictionary();
    }

    HRESULT AdaptiveCardRenderer::get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary)
    {
        return m_overrideDictionary.CopyTo(overrideDictionary);
    }

    HRESULT AdaptiveCardRenderer::put_HostConfig(_In_ IAdaptiveHostConfig* hostConfig)
    {
        m_hostConfig = hostConfig;
        UpdateActionSentimentResourceDictionary();
        return S_OK;
    }

    HRESULT AdaptiveCardRenderer::get_HostConfig(_COM_Outptr_ IAdaptiveHostConfig** hostConfig)
    {
        return m_hostConfig.CopyTo(hostConfig);
    }

    HRESULT AdaptiveCardRenderer::put_FeatureRegistration(_In_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration* featureRegistration)
    {
        m_featureRegistration = featureRegistration;
        return S_OK;
    }

    HRESULT AdaptiveCardRenderer::get_FeatureRegistration(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration** featureRegistration)
    {
        if (!m_featureRegistration)
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFeatureRegistration>(m_featureRegistration.GetAddressOf()));
        }

        return m_featureRegistration.CopyTo(featureRegistration);
    }

    HRESULT AdaptiveCardRenderer::SetFixedDimensions(UINT32 desiredWidth, UINT32 desiredHeight)
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

    HRESULT AdaptiveCardRenderer::RenderAdaptiveCard(_In_ IAdaptiveCard* adaptiveCard, _COM_Outptr_ IRenderedAdaptiveCard** result)
    {
        ComPtr<::AdaptiveNamespace::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::RenderedAdaptiveCard>(&renderedCard));
        renderedCard->SetOriginatingCard(adaptiveCard);
        renderedCard->SetOriginatingHostConfig(m_hostConfig.Get());

        if (adaptiveCard)
        {
            ComPtr<IFrameworkElement> xamlTreeRoot;

            if (m_explicitDimensions)
            {
                m_xamlBuilder->SetFixedDimensions(m_desiredWidth, m_desiredHeight);
            }

            ComPtr<AdaptiveRenderContext> renderContext;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderContext>(&renderContext,
                                                                      m_hostConfig.Get(),
                                                                      m_featureRegistration.Get(),
                                                                      m_elementRendererRegistration.Get(),
                                                                      m_actionRendererRegistration.Get(),
                                                                      m_resourceResolvers.Get(),
                                                                      m_mergedResourceDictionary.Get(),
                                                                      m_actionSentimentResourceDictionary.Get(),
                                                                      renderedCard.Get()));

            // This path is used for synchronous Xaml card rendering, so we don't want
            // to manually download the image assets and instead just want xaml to do
            // that automatically
            m_xamlBuilder->SetEnableXamlImageHandling(true);
            try
            {
                AdaptiveNamespace::XamlBuilder::BuildXamlTreeFromAdaptiveCard(adaptiveCard, &xamlTreeRoot, renderContext.Get(), m_xamlBuilder);
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

    HRESULT AdaptiveCardRenderer::RenderCardAsXamlAsync(_In_ IAdaptiveCard* adaptiveCard,
                                                        _COM_Outptr_ IAsyncOperation<ABI::AdaptiveNamespace::RenderedAdaptiveCard*>** result)
    {
        *result = Make<RenderCardAsXamlAsyncOperation>(adaptiveCard, this).Detach();
        return S_OK;
    }

    HRESULT AdaptiveCardRenderer::RenderAdaptiveCardFromJsonString(_In_ HSTRING adaptiveJson,
                                                                   _COM_Outptr_ IRenderedAdaptiveCard** result)
    {
        ComPtr<::AdaptiveNamespace::RenderedAdaptiveCard> renderedCard;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::RenderedAdaptiveCard>(&renderedCard));

        ComPtr<IAdaptiveCardParseResult> adaptiveCardParseResult;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCardParseResult));
        ComPtr<IAdaptiveCard> parsedCard;
        RETURN_IF_FAILED(adaptiveCardParseResult->get_AdaptiveCard(&parsedCard));
        if (parsedCard == nullptr)
        {
            ComPtr<IVector<AdaptiveError*>> renderResultErrors;
            RETURN_IF_FAILED(renderedCard->get_Errors(&renderResultErrors));
            ComPtr<IVector<AdaptiveError*>> parseErrors;
            RETURN_IF_FAILED(adaptiveCardParseResult->get_Errors(&parseErrors));
            XamlHelpers::IterateOverVector<AdaptiveError, IAdaptiveError>(parseErrors.Get(), [&](IAdaptiveError* error) {
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

    HRESULT AdaptiveCardRenderer::RenderAdaptiveCardFromJson(_In_ IJsonObject* adaptiveJson,
                                                             _COM_Outptr_ IRenderedAdaptiveCard** result)
    {
        HString adaptiveJsonAsHstring;
        RETURN_IF_FAILED(JsonObjectToHString(adaptiveJson, adaptiveJsonAsHstring.GetAddressOf()));
        return RenderAdaptiveCardFromJsonString(adaptiveJsonAsHstring.Get(), result);
    }

    HRESULT AdaptiveCardRenderer::RenderAdaptiveJsonAsXamlAsync(_In_ HSTRING adaptiveJson,
                                                                _COM_Outptr_ IAsyncOperation<ABI::AdaptiveNamespace::RenderedAdaptiveCard*>** result)
    {
        ComPtr<IAdaptiveCardParseResult> adaptiveCardParseResult;
        RETURN_IF_FAILED(CreateAdaptiveCardFromJsonString(adaptiveJson, &adaptiveCardParseResult));

        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(adaptiveCardParseResult->get_AdaptiveCard(&adaptiveCard));
        return RenderCardAsXamlAsync(adaptiveCard.Get(), result);
    }

    HRESULT AdaptiveCardRenderer::CreateAdaptiveCardFromJsonString(_In_ HSTRING adaptiveJson,
                                                                   _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** parseResult)
    {
        ComPtr<IAdaptiveCardStatics> adaptiveCardStatics;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardStaticsImpl>(&adaptiveCardStatics));
        return adaptiveCardStatics->FromJsonString(adaptiveJson, parseResult);
    }

    IAdaptiveHostConfig* AdaptiveCardRenderer::GetHostConfig() { return m_hostConfig.Get(); }

    HRESULT AdaptiveCardRenderer::get_ResourceResolvers(_COM_Outptr_ IAdaptiveCardResourceResolvers** value)
    {
        return m_resourceResolvers.CopyTo(value);
    }

    ComPtr<IResourceDictionary> AdaptiveCardRenderer::GetMergedDictionary() { return m_mergedResourceDictionary; }

    ComPtr<IResourceDictionary> AdaptiveCardRenderer::GetActionSentimentResourceDictionary()
    {
        return m_actionSentimentResourceDictionary;
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

    HRESULT AdaptiveCardRenderer::get_ElementRenderers(_COM_Outptr_ IAdaptiveElementRendererRegistration** value)
    {
        return m_elementRendererRegistration.CopyTo(value);
    }

    HRESULT AdaptiveCardRenderer::get_ActionRenderers(_COM_Outptr_ IAdaptiveActionRendererRegistration** value)
    {
        return m_actionRendererRegistration.CopyTo(value);
    }

    void AdaptiveCardRenderer::InitializeDefaultResourceDictionary()
    {
        ComPtr<IXamlReaderStatics> xamlReaderStatics;
        THROW_IF_FAILED(RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Markup_XamlReader).Get(),
                                               __uuidof(IXamlReaderStatics),
                                               reinterpret_cast<void**>(xamlReaderStatics.GetAddressOf())));

        ComPtr<IInspectable> resourceDictionaryInspectable;
        THROW_IF_FAILED(xamlReaderStatics->Load(HStringReference(c_defaultResourceDictionary).Get(), &resourceDictionaryInspectable));
        ComPtr<IResourceDictionary> resourceDictionary;
        THROW_IF_FAILED(resourceDictionaryInspectable.As(&resourceDictionary));

        m_mergedResourceDictionary = resourceDictionary;
        m_defaultResourceDictionary = resourceDictionary;

        ComPtr<IInspectable> actionSentimentResourceDictionaryInspectable;
        THROW_IF_FAILED(xamlReaderStatics->Load(HStringReference(c_defaultActionSentimentResourceDictionary).Get(),
                                                &actionSentimentResourceDictionaryInspectable));
        ComPtr<IResourceDictionary> actionSentimentResourceDictionary;
        THROW_IF_FAILED(actionSentimentResourceDictionaryInspectable.As(&actionSentimentResourceDictionary));

        m_actionSentimentResourceDictionary = actionSentimentResourceDictionary;
    }

    HRESULT AdaptiveCardRenderer::TryInsertResourceToSentimentResourceDictionary(const std::wstring& resourceName,
                                                                                 _In_ IInspectable* value)
    {
        ComPtr<IPropertyValueStatics> propertyValueStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(),
                                              &propertyValueStatics));

        ComPtr<IInspectable> resourceKey;
        RETURN_IF_FAILED(propertyValueStatics->CreateString(HStringReference(resourceName.c_str()).Get(), resourceKey.GetAddressOf()));

        ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;
        RETURN_IF_FAILED(m_actionSentimentResourceDictionary.As(&resourceDictionaryMap));

        boolean replaced{};
        RETURN_IF_FAILED(resourceDictionaryMap->Insert(resourceKey.Get(), value, &replaced));
        return S_OK;
    }

    void AdaptiveCardRenderer::UpdateActionSentimentResourceDictionary()
    {
        ABI::Windows::UI::Color accentColor;
        THROW_IF_FAILED(GetColorFromAdaptiveColor(m_hostConfig.Get(),
                                                  ABI::AdaptiveNamespace::ForegroundColor_Accent,
                                                  ABI::AdaptiveNamespace::ContainerStyle_Default,
                                                  false, // isSubtle
                                                  false, // highlight
                                                  &accentColor));

        ABI::Windows::UI::Color attentionColor;
        THROW_IF_FAILED(GetColorFromAdaptiveColor(m_hostConfig.Get(),
                                                  ABI::AdaptiveNamespace::ForegroundColor_Attention,
                                                  ABI::AdaptiveNamespace::ContainerStyle_Default,
                                                  false, // isSubtle
                                                  false, // highlight
                                                  &attentionColor));

        ABI::Windows::UI::Color lighterAccentColor = GenerateLighterColor(accentColor);
        ABI::Windows::UI::Color lighterAttentionColor = GenerateLighterColor(attentionColor);

        ComPtr<IBrush> accentColorBrush = XamlHelpers::GetSolidColorBrush(accentColor);
        THROW_IF_FAILED(TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Positive.Button.Static.Background",
                                                                       accentColorBrush.Get()));

        ComPtr<IBrush> lightAccentColorBrush = XamlHelpers::GetSolidColorBrush(lighterAccentColor);
        THROW_IF_FAILED(TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Positive.Button.MouseOver.Background",
                                                                       lightAccentColorBrush.Get()));

        ComPtr<IBrush> attentionColorBrush = XamlHelpers::GetSolidColorBrush(attentionColor);
        THROW_IF_FAILED(TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Destructive.Button.Foreground",
                                                                       attentionColorBrush.Get()));

        ComPtr<IBrush> lightAttentionColorBrush = XamlHelpers::GetSolidColorBrush(lighterAttentionColor);
        THROW_IF_FAILED(TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Destructive.Button.MouseOver.Foreground",
                                                                       lightAttentionColorBrush.Get()));
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

    ComPtr<XamlBuilder> AdaptiveCardRenderer::GetXamlBuilder() { return m_xamlBuilder; }
}
