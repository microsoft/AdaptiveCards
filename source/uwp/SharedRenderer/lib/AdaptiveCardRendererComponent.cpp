// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardRendererComponent.h"
#include "AdaptiveCardRenderer.g.cpp"

#include "AdaptiveCardResourceResolvers.h"
#include "AdaptiveActionRendererRegistration.h"
#include "AdaptiveActionSetRenderer.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveColumnRenderer.h"
#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveDateInputRenderer.h"
#include "AdaptiveElementRendererRegistration.h"
#include "AdaptiveExecuteActionRenderer.h"
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
#include "AdaptiveTableRenderer.h"
#include "AdaptiveTextBlockRenderer.h"
#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveToggleVisibilityActionRenderer.h"
#include "AdaptiveToggleInputRenderer.h"
#include "DefaultResourceDictionary.h"
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveCardRenderer::AdaptiveCardRenderer() :
        m_elementRendererRegistration(winrt::make_self<implementation::AdaptiveElementRendererRegistration>()),
        m_actionRendererRegistration(winrt::make_self<implementation::AdaptiveActionRendererRegistration>()),
        m_featureRegistration(winrt::make<implementation::AdaptiveFeatureRegistration>()),
        m_hostConfig(winrt::make<implementation::AdaptiveHostConfig>()),
        m_resourceResolvers(winrt::make<implementation::AdaptiveCardResourceResolvers>()),
        m_xamlBuilder(winrt::make_self<::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder>())
    {
        ::AdaptiveCards::Rendering::Xaml_Rendering::RegisterDefaultElementRenderers(m_elementRendererRegistration.get(), m_xamlBuilder);
        ::AdaptiveCards::Rendering::Xaml_Rendering::RegisterDefaultActionRenderers(m_actionRendererRegistration.get());
        InitializeDefaultResourceDictionary();
        UpdateActionSentimentResourceDictionary();
    }

    winrt::AdaptiveFeatureRegistration AdaptiveCardRenderer::FeatureRegistration()
    {
        if (!m_featureRegistration)
        {
            m_featureRegistration = winrt::make<implementation::AdaptiveFeatureRegistration>();
        }
        return m_featureRegistration;
    }

    void AdaptiveCardRenderer::SetFixedDimensions(uint32_t desiredWidth, uint32_t desiredHeight)
    {
        m_explicitDimensions = true;
        m_desiredWidth = desiredWidth;
        m_desiredHeight = desiredHeight;
    }

    bool AdaptiveCardRenderer::OverflowMaxActions()
    {
        return GetHostConfig()->OverflowMaxActions;
    }

    void AdaptiveCardRenderer::OverflowMaxActions(bool overflowMaxActions)
    {
        GetHostConfig()->OverflowMaxActions = overflowMaxActions;
    }

    winrt::RenderedAdaptiveCard AdaptiveCardRenderer::RenderAdaptiveCard(winrt::AdaptiveCard const& adaptiveCard)
    {
        auto renderedCard = winrt::make_self<implementation::RenderedAdaptiveCard>();
        renderedCard->SetOriginatingCard(adaptiveCard);
        renderedCard->SetOriginatingHostConfig(m_hostConfig);

        if (adaptiveCard)
        {
            if (m_explicitDimensions)
            {
                m_xamlBuilder->SetFixedDimensions(m_desiredWidth, m_desiredHeight);
            }

            auto renderContext = winrt::make_self<implementation::AdaptiveRenderContext>(m_hostConfig,
                                                                                         m_featureRegistration,
                                                                                         *m_elementRendererRegistration,
                                                                                         *m_actionRendererRegistration,
                                                                                         m_resourceResolvers,
                                                                                         m_mergedResourceDictionary,
                                                                                         m_actionSentimentResourceDictionary,
                                                                                         renderedCard);

            m_xamlBuilder->SetEnableXamlImageHandling(true);
            try
            {
                renderContext->LinkCardToParent(adaptiveCard, nullptr);
                auto xamlTreeRoot =
                    ::AdaptiveCards::Rendering::Xaml_Rendering::XamlBuilder::BuildXamlTreeFromAdaptiveCard(adaptiveCard, *renderContext, m_xamlBuilder.get());
                renderedCard->SetFrameworkElement(xamlTreeRoot);
            }
            catch (...)
            {
                renderContext->AddError(winrt::ErrorStatusCode::RenderFailed,
                                        L"An unrecoverable error was encountered while rendering the card");
                renderedCard->SetFrameworkElement(nullptr);
            }
        }

        return *renderedCard;
    }

    winrt::RenderedAdaptiveCard AdaptiveCardRenderer::RenderAdaptiveCardFromJsonString(hstring const& adaptiveJson)
    {
        auto adaptiveCardParseResult = winrt::AdaptiveCard::FromJsonString(adaptiveJson);
        if (auto parsedCard = adaptiveCardParseResult.AdaptiveCard())
        {
            return RenderAdaptiveCard(parsedCard);
        }
        else
        {
            // Replicate parse errors into render errors
            auto renderedCard = winrt::make_self<implementation::RenderedAdaptiveCard>();
            auto renderResultErrors = renderedCard->Errors.get();
            for (auto&& error : adaptiveCardParseResult.Errors())
            {
                renderResultErrors.Append(error);
            }

            return *renderedCard;
        }
    }

    winrt::RenderedAdaptiveCard AdaptiveCardRenderer::RenderAdaptiveCardFromJson(winrt::JsonObject const& adaptiveJson)
    {
        return RenderAdaptiveCardFromJsonString(JsonObjectToHString(adaptiveJson));
    }

    bool AdaptiveCardRenderer::GetFixedDimensions(_Out_ uint32_t* width, _Out_ uint32_t* height)
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

    void AdaptiveCardRenderer::InitializeDefaultResourceDictionary()
    {
        auto resourceDictionary = winrt::XamlReader::Load(c_defaultResourceDictionary).as<winrt::ResourceDictionary>();
        m_mergedResourceDictionary = resourceDictionary;
        m_defaultResourceDictionary = resourceDictionary;

        auto actionSentimentResourceDictionary =
            winrt::XamlReader::Load(c_defaultActionSentimentResourceDictionary).as<winrt::ResourceDictionary>();
        m_actionSentimentResourceDictionary = actionSentimentResourceDictionary;
    }

    void AdaptiveCardRenderer::TryInsertResourceToSentimentResourceDictionary(std::wstring_view const& resourceName,
                                                                              winrt::IInspectable const& value)
    {
        m_actionSentimentResourceDictionary.Insert(winrt::box_value(resourceName), value);
    }

    void AdaptiveCardRenderer::UpdateActionSentimentResourceDictionary()
    {
        auto accentColor =
            GetColorFromAdaptiveColor(m_hostConfig, winrt::ForegroundColor::Accent, winrt::ContainerStyle::Default, false, false);
        auto attentionColor =
            GetColorFromAdaptiveColor(m_hostConfig, winrt::ForegroundColor::Attention, winrt::ContainerStyle::Default, false, false);

        auto hoverAccentColor = GenerateLHoverColor(accentColor);
        auto hoverAttentionColor = GenerateLHoverColor(attentionColor);

        TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Positive.Button.Static.Background",
                                                       winrt::SolidColorBrush{accentColor});

        TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Positive.Button.MouseOver.Background",
                                                       winrt::SolidColorBrush{hoverAccentColor});

        TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Destructive.Button.Foreground",
                                                       winrt::SolidColorBrush{attentionColor});
        TryInsertResourceToSentimentResourceDictionary(L"Adaptive.Action.Destructive.Button.MouseOver.Foreground",
                                                       winrt::SolidColorBrush{hoverAttentionColor});
    }

    void AdaptiveCardRenderer::SetMergedDictionary()
    {
        if (m_overrideDictionary)
        {
            m_mergedResourceDictionary = m_overrideDictionary;
            m_mergedResourceDictionary.MergedDictionaries().Append(m_defaultResourceDictionary);
        }
    }
}
