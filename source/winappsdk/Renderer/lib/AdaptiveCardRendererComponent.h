// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "XamlBuilder.h"
#include "AdaptiveCardRenderer.g.h"
#include "AdaptiveHostConfig.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    namespace rtxaml = ::winrt::Windows::UI::Xaml;

    // This class is effectively a singleton, and stays around between subsequent renders.
    struct AdaptiveCardRenderer : AdaptiveCardRendererT<AdaptiveCardRenderer>
    {
    private:
        rtxaml::ResourceDictionary m_overrideDictionary;
        WinUI3::AdaptiveHostConfig m_hostConfig;
        WinUI3::AdaptiveFeatureRegistration m_featureRegistration;
        winrt::com_ptr<::AdaptiveCards::Rendering::WinUI3::XamlBuilder> m_xamlBuilder;
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
        void OverrideStyles(rtxaml::ResourceDictionary const& overrideDictionary)
        {
            m_overrideDictionary = overrideDictionary;
            SetMergedDictionary();
        }

        rtxaml::ResourceDictionary OverrideStyles() { return m_overrideDictionary; }

        void HostConfig(WinUI3::AdaptiveHostConfig const& hostConfig)
        {
            m_hostConfig = hostConfig;
            UpdateActionSentimentResourceDictionary();
        }

        WinUI3::AdaptiveHostConfig HostConfig() { return m_hostConfig; }

        void FeatureRegistration(WinUI3::AdaptiveFeatureRegistration const& featureRegistration)
        {
            m_featureRegistration = featureRegistration;
        }

        WinUI3::AdaptiveFeatureRegistration FeatureRegistration();

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

        WinUI3::RenderedAdaptiveCard RenderAdaptiveCard(ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard);
        WinUI3::RenderedAdaptiveCard RenderAdaptiveCardFromJsonString(hstring const& adaptiveJson);
        WinUI3::RenderedAdaptiveCard RenderAdaptiveCardFromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson);

        WinUI3::AdaptiveElementRendererRegistration ElementRenderers() { return *m_elementRendererRegistration; }
        WinUI3::AdaptiveActionRendererRegistration ActionRenderers() { return *m_actionRendererRegistration; }

        rtxaml::ResourceDictionary GetMergedDictionary() { return m_mergedResourceDictionary; }
        bool GetFixedDimensions(_Out_ uint32_t* width, _Out_ uint32_t* height);
        winrt::com_ptr<::AdaptiveCards::Rendering::WinUI3::XamlBuilder> GetXamlBuilder() { return m_xamlBuilder; }
        rtxaml::ResourceDictionary GetActionSentimentResourceDictionary()
        {
            return m_actionSentimentResourceDictionary;
        }

        auto ResourceResolvers() { return m_resourceResolvers; }

    private:
        void InitializeDefaultResourceDictionary();
        void UpdateActionSentimentResourceDictionary();
        void TryInsertResourceToSentimentResourceDictionary(std::wstring_view const& resourceName, winrt::Windows::Foundation::IInspectable const& value);
        void SetMergedDictionary();

        rtxaml::ResourceDictionary m_defaultResourceDictionary;
        rtxaml::ResourceDictionary m_mergedResourceDictionary;
        rtxaml::ResourceDictionary m_actionSentimentResourceDictionary;
        WinUI3::AdaptiveCardResourceResolvers m_resourceResolvers;
        winrt::com_ptr<implementation::AdaptiveElementRendererRegistration> m_elementRendererRegistration;
        winrt::com_ptr<implementation::AdaptiveActionRendererRegistration> m_actionRendererRegistration;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveCardRenderer : AdaptiveCardRendererT<AdaptiveCardRenderer, implementation::AdaptiveCardRenderer>
    {
    };
}
