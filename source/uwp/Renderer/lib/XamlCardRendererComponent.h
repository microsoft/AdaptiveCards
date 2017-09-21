#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    // This class is effectively a singleton, and stays around between subsequent renders.
    class XamlCardRenderer :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::XamlCardRenderer::IXamlCardRenderer>,
            Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardRenderer, BaseTrust)

    public:
        XamlCardRenderer();
        HRESULT RuntimeClassInitialize();

        // IXamlCardRenderer
        IFACEMETHODIMP SetRenderOptions(_In_ ABI::AdaptiveCards::XamlCardRenderer::RenderOptions options);
        IFACEMETHODIMP SetOverrideStyles(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary);
        IFACEMETHODIMP SetHostConfig(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* hostConfig);
        IFACEMETHODIMP SetFixedDimensions(_In_ UINT32 desiredWidth, _In_ UINT32 desiredHeight);
        IFACEMETHODIMP ResetFixedDimensions();

        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::XamlCardRenderer*, ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token);

        IFACEMETHODIMP remove_Action(
            _In_ EventRegistrationToken token);

        IFACEMETHODIMP RenderCardAsXaml(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);
        IFACEMETHODIMP RenderCardAsXamlAsync(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::Windows::Foundation::IAsyncOperation<ABI::Windows::UI::Xaml::UIElement*>** result);

        IFACEMETHODIMP RenderAdaptiveJsonAsXaml(_In_ HSTRING adaptiveJson, 
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result);
        IFACEMETHODIMP RenderAdaptiveJsonAsXamlAsync(_In_ HSTRING adaptiveJson,
            _COM_Outptr_ ABI::Windows::Foundation::IAsyncOperation<ABI::Windows::UI::Xaml::UIElement*>** result);

        HRESULT SendActionEvent(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs* eventArgs);
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* GetHostConfig();
        ABI::Windows::UI::Xaml::IResourceDictionary* GetOverrideDictionary();
        bool GetFixedDimensions(_Out_ UINT32* width, _Out_ UINT32* height);

        IFACEMETHODIMP get_ResourceResolvers(
            _COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolvers** value);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolvers> m_resourceResolvers;

        bool m_explicitDimensions = false;
        UINT32 m_desiredWidth = 0;
        UINT32 m_desiredHeight = 0;

        std::shared_ptr<ActionEventSource> m_events;

        HRESULT CreateAdaptiveCardFromJson(_In_ HSTRING adaptiveJson, _COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** adaptiveCard);
    };

    ActivatableClass(XamlCardRenderer);
}}