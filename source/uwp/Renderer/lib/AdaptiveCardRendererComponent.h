#pragma once

#include "AdaptiveCards.Uwp.h"
#include "XamlBuilder.h"

namespace AdaptiveCards { namespace Uwp
{
    class XamlBuilder;

    // This class is effectively a singleton, and stays around between subsequent renders.
    class AdaptiveCardRenderer :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveCardRenderer>,
            Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveCardRenderer, BaseTrust)

    public:
        AdaptiveCardRenderer();
        HRESULT RuntimeClassInitialize();

        // IAdaptiveCardRenderer
        IFACEMETHODIMP SetOverrideStyles(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary);
        IFACEMETHODIMP put_HostConfig(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig);
        IFACEMETHODIMP get_HostConfig(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig** hostConfig);
        IFACEMETHODIMP SetFixedDimensions(_In_ UINT32 desiredWidth, _In_ UINT32 desiredHeight);
        IFACEMETHODIMP ResetFixedDimensions();

        IFACEMETHODIMP RenderAdaptiveCard(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IRenderedAdaptiveCard** result);
        HRESULT RenderCardAsXamlAsync(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::Windows::Foundation::IAsyncOperation<ABI::Windows::UI::Xaml::UIElement*>** result);

        IFACEMETHODIMP RenderAdaptiveCardFromJsonString(_In_ HSTRING adaptiveJson, 
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IRenderedAdaptiveCard** result);
        HRESULT RenderAdaptiveJsonAsXamlAsync(_In_ HSTRING adaptiveJson,
            _COM_Outptr_ ABI::Windows::Foundation::IAsyncOperation<ABI::Windows::UI::Xaml::UIElement*>** result);

        IFACEMETHODIMP RenderAdaptiveCardFromJson(_In_ ABI::Windows::Data::Json::IJsonObject* adaptiveJson,
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IRenderedAdaptiveCard** result);

        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration** result);
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration** result);

        ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* GetHostConfig();
        ABI::Windows::UI::Xaml::IResourceDictionary* GetOverrideDictionary();
        bool GetFixedDimensions(_Out_ UINT32* width, _Out_ UINT32* height);

        IFACEMETHODIMP get_ResourceResolvers(
            _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolvers** value);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;

        std::shared_ptr<AdaptiveCards::Uwp::XamlBuilder> m_xamlBuilder;
        HRESULT RegisterDefaultElementRenderers();
        HRESULT RegisterDefaultActionRenderers();

        bool m_explicitDimensions = false;
        UINT32 m_desiredWidth = 0;
        UINT32 m_desiredHeight = 0;

        HRESULT CreateAdaptiveCardFromJsonString(_In_ HSTRING adaptiveJson, _COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardParseResult** adaptiveCard);
    };

    ActivatableClass(AdaptiveCardRenderer);
}}
