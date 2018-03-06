#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveRenderContext :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveRenderContext, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration* elementRendererRegistration,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers* resourceResolvers,
            ABI::Windows::UI::Xaml::IResourceDictionary* overrideStyles,
            AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig** value);
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration** value);
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionInvoker** value);
        IFACEMETHODIMP AddInputValue(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue* inputValue);
        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers** value);
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary);
        IFACEMETHODIMP AddError(_In_ ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode statusCode, _In_ HSTRING message);
        IFACEMETHODIMP AddWarning(_In_ ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode statusCode, _In_ HSTRING message);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard> m_renderResult;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveActionInvoker> m_actionInvoker;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
    };

    ActivatableClass(AdaptiveRenderContext);
}}}
