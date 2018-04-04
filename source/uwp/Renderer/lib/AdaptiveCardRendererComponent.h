#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "XamlBuilder.h"

AdaptiveNamespaceStart
    class XamlBuilder;

    // This class is effectively a singleton, and stays around between subsequent renders.
    class AdaptiveCardRenderer :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IAdaptiveCardRenderer>,
            Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveCardRenderer)

    public:
        HRESULT RuntimeClassInitialize();

        // IAdaptiveCardRenderer
        IFACEMETHODIMP put_OverrideStyles(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary);
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary);
        IFACEMETHODIMP put_HostConfig(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig);
        IFACEMETHODIMP get_HostConfig(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig** hostConfig);
        IFACEMETHODIMP SetFixedDimensions(_In_ UINT32 desiredWidth, _In_ UINT32 desiredHeight);
        IFACEMETHODIMP ResetFixedDimensions();

        IFACEMETHODIMP RenderAdaptiveCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::AdaptiveNamespace::IRenderedAdaptiveCard** result);
        HRESULT RenderCardAsXamlAsync(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::Windows::Foundation::IAsyncOperation<ABI::AdaptiveNamespace::RenderedAdaptiveCard*>** result);

        IFACEMETHODIMP RenderAdaptiveCardFromJsonString(_In_ HSTRING adaptiveJson,
            _COM_Outptr_ ABI::AdaptiveNamespace::IRenderedAdaptiveCard** result);
        HRESULT RenderAdaptiveJsonAsXamlAsync(_In_ HSTRING adaptiveJson,
            _COM_Outptr_ ABI::Windows::Foundation::IAsyncOperation<ABI::AdaptiveNamespace::RenderedAdaptiveCard*>** result);

        IFACEMETHODIMP RenderAdaptiveCardFromJson(_In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
            _COM_Outptr_ ABI::AdaptiveNamespace::IRenderedAdaptiveCard** result);

        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveElementRendererRegistration** result);

        ABI::AdaptiveNamespace::IAdaptiveHostConfig* GetHostConfig();
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> GetMergedDictionary();
        bool GetFixedDimensions(_Out_ UINT32* width, _Out_ UINT32* height);
        std::shared_ptr<AdaptiveNamespace::XamlBuilder> GetXamlBuilder();

        IFACEMETHODIMP get_ResourceResolvers(
            _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers** value);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_defaultResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_mergedResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;

        std::shared_ptr<AdaptiveNamespace::XamlBuilder> m_xamlBuilder;
        bool m_explicitDimensions = false;
        UINT32 m_desiredWidth = 0;
        UINT32 m_desiredHeight = 0;

        HRESULT CreateAdaptiveCardFromJsonString(_In_ HSTRING adaptiveJson, _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardParseResult** adaptiveCard);
        HRESULT RegisterDefaultElementRenderers();
        void InitializeDefaultResourceDictionary();
        HRESULT SetMergedDictionary();
    };

    ActivatableClass(AdaptiveCardRenderer);
AdaptiveNamespaceEnd