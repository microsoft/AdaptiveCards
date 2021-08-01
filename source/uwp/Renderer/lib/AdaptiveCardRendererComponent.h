// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "XamlBuilder.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class XamlBuilder;

    // This class is effectively a singleton, and stays around between subsequent renders.
    class AdaptiveCardRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardRenderer>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveCardRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveCardRenderer
        IFACEMETHODIMP put_OverrideStyles(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary);
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary);
        IFACEMETHODIMP put_HostConfig(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig);
        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig** hostConfig);
        IFACEMETHODIMP put_FeatureRegistration(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration* featureRegistration);
        IFACEMETHODIMP get_FeatureRegistration(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration** featureRegistration);
        IFACEMETHODIMP SetFixedDimensions(UINT32 desiredWidth, UINT32 desiredHeight);
        IFACEMETHODIMP ResetFixedDimensions();

        IFACEMETHODIMP RenderAdaptiveCard(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* adaptiveCard,
                                          _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IRenderedAdaptiveCard** result);

        IFACEMETHODIMP RenderAdaptiveCardFromJsonString(_In_ HSTRING adaptiveJson,
                                                        _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IRenderedAdaptiveCard** result);

        IFACEMETHODIMP RenderAdaptiveCardFromJson(_In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
                                                  _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IRenderedAdaptiveCard** result);

        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration** result);
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionRendererRegistration** result);

        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* GetHostConfig();
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> GetMergedDictionary();
        bool GetFixedDimensions(_Out_ UINT32* width, _Out_ UINT32* height);
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::XamlBuilder> GetXamlBuilder();
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> GetActionSentimentResourceDictionary();

        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers** value);

    private:
        void InitializeDefaultResourceDictionary();
        void UpdateActionSentimentResourceDictionary();
        HRESULT TryInsertResourceToSentimentResourceDictionary(const std::wstring& resourceName, _In_ IInspectable* value);
        HRESULT SetMergedDictionary();

        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_defaultResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_mergedResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_actionSentimentResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration> m_featureRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;

        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::XamlBuilder> m_xamlBuilder;
        bool m_explicitDimensions = false;
        UINT32 m_desiredWidth = 0;
        UINT32 m_desiredHeight = 0;
    };

    ActivatableClass(AdaptiveCardRenderer);
}
