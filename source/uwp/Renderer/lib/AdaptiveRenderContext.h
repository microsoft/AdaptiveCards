#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"

AdaptiveNamespaceStart
    class AdaptiveRenderContext :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveRenderContext>
    {
        AdaptiveRuntime(AdaptiveRenderContext)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig* hostConfig,
            ABI::AdaptiveNamespaceRef::IAdaptiveElementRendererRegistration* elementRendererRegistration,
            ABI::AdaptiveNamespaceRef::IAdaptiveCardResourceResolvers* resourceResolvers,
            ABI::Windows::UI::Xaml::IResourceDictionary* overrideStyles,
            AdaptiveNamespaceRef::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig** value);
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveElementRendererRegistration** value);
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveActionInvoker** value);
        IFACEMETHODIMP AddInputValue(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveInputValue* inputValue);
        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveCardResourceResolvers** value);
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary);
        IFACEMETHODIMP AddError(_In_ ABI::AdaptiveNamespaceRef::ErrorStatusCode statusCode, _In_ HSTRING message);
        IFACEMETHODIMP AddWarning(_In_ ABI::AdaptiveNamespaceRef::WarningStatusCode statusCode, _In_ HSTRING message);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<AdaptiveNamespaceRef::RenderedAdaptiveCard> m_renderResult;
        Microsoft::WRL::ComPtr<AdaptiveNamespaceRef::AdaptiveActionInvoker> m_actionInvoker;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
    };

    ActivatableClass(AdaptiveRenderContext);
AdaptiveNamespaceEnd
