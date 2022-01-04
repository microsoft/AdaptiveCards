// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "XamlBuilder.h"
#include "AdaptiveCardRenderer.g.h"
#include "AdaptiveHostConfig.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    // This class is effectively a singleton, and stays around between subsequent renders.
    struct AdaptiveCardRenderer : AdaptiveCardRendererT<AdaptiveCardRenderer>
    {
    private:
        winrt::ResourceDictionary m_overrideDictionary;
        Uwp::AdaptiveHostConfig m_hostConfig;
        Uwp::AdaptiveFeatureRegistration m_featureRegistration;
        winrt::com_ptr<::AdaptiveCards::Rendering::Uwp::XamlBuilder> m_xamlBuilder;
        bool m_explicitDimensions = false;
        uint32_t m_desiredWidth = 0;
        uint32_t m_desiredHeight = 0;

        winrt::com_ptr<implementation::AdaptiveHostConfig> GetHostConfig()
        {
            return peek_innards<implementation::AdaptiveHostConfig>(m_hostConfig);
        }

    public:
        AdaptiveCardRenderer();

        // IAdaptiveCardRenderer
        void OverrideStyles(winrt::ResourceDictionary const& overrideDictionary)
        {
            m_overrideDictionary = overrideDictionary;
            SetMergedDictionary();
        }

        winrt::ResourceDictionary OverrideStyles() { return m_overrideDictionary; }

        void HostConfig(winrt::AdaptiveHostConfig const& hostConfig)
        {
            m_hostConfig = hostConfig;
            UpdateActionSentimentResourceDictionary();
        }

        Uwp::AdaptiveHostConfig HostConfig() { return m_hostConfig; }

        void FeatureRegistration(winrt::AdaptiveFeatureRegistration const& featureRegistration)
        {
            m_featureRegistration = featureRegistration;
        }

        Uwp::AdaptiveFeatureRegistration FeatureRegistration();

        void SetFixedDimensions(uint32_t desiredWidth, uint32_t desiredHeight);
        void ResetFixedDimensions() { m_explicitDimensions = false; };

        void OverflowMaxActions(bool overflowMaxActions);
        bool OverflowMaxActions();

        hstring OverflowButtonText() { return GetHostConfig()->OverflowButtonText; }
        void OverflowButtonText(hstring const& overflowButtonText)
        {
            return GetHostConfig()->OverflowButtonText = overflowButtonText;
        }

        hstring OverflowButtonAccessibilityText() { return GetHostConfig()->OverflowButtonAccessibilityText; }
        void OverflowButtonAccessibilityText(hstring const& text)
        {
            return GetHostConfig()->OverflowButtonAccessibilityText = text;
        }

        Uwp::RenderedAdaptiveCard RenderAdaptiveCard(winrt::AdaptiveCard const& adaptiveCard);
        Uwp::RenderedAdaptiveCard RenderAdaptiveCardFromJsonString(hstring const& adaptiveJson);
        Uwp::RenderedAdaptiveCard RenderAdaptiveCardFromJson(winrt::JsonObject const& adaptiveJson);

        Uwp::AdaptiveElementRendererRegistration ElementRenderers() { return *m_elementRendererRegistration; }
        Uwp::AdaptiveActionRendererRegistration ActionRenderers() { return *m_actionRendererRegistration; }

        winrt::ResourceDictionary GetMergedDictionary() { return m_mergedResourceDictionary; }
        bool GetFixedDimensions(_Out_ uint32_t* width, _Out_ uint32_t* height);
        winrt::com_ptr<::AdaptiveCards::Rendering::Uwp::XamlBuilder> GetXamlBuilder() { return m_xamlBuilder; }
        winrt::ResourceDictionary GetActionSentimentResourceDictionary()
        {
            return m_actionSentimentResourceDictionary;
        }

        auto ResourceResolvers() { return m_resourceResolvers; }

    private:
        void InitializeDefaultResourceDictionary();
        void UpdateActionSentimentResourceDictionary();
        void TryInsertResourceToSentimentResourceDictionary(std::wstring_view const& resourceName, winrt::IInspectable const& value);
        void SetMergedDictionary();

        winrt::ResourceDictionary m_defaultResourceDictionary;
        winrt::ResourceDictionary m_mergedResourceDictionary;
        winrt::ResourceDictionary m_actionSentimentResourceDictionary;
        Uwp::AdaptiveCardResourceResolvers m_resourceResolvers;
        winrt::com_ptr<implementation::AdaptiveElementRendererRegistration> m_elementRendererRegistration;
        winrt::com_ptr<implementation::AdaptiveActionRendererRegistration> m_actionRendererRegistration;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveCardRenderer : AdaptiveCardRendererT<AdaptiveCardRenderer, implementation::AdaptiveCardRenderer>
    {
    };
}
