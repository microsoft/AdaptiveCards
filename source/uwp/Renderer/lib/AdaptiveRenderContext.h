#pragma once

#include "AdaptiveCards.Uwp.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveRenderContext :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveRenderContext, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig,
            ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration* elementRendererRegistration,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolvers* resourceResolvers,
            ABI::Windows::UI::Xaml::IResourceDictionary* overrideStyles,
            AdaptiveCards::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig** value);
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration** value);
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionInvoker** value);
        IFACEMETHODIMP AddInputItem(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* cardElement, _In_ ABI::Windows::UI::Xaml::IUIElement* uiElement);
        IFACEMETHODIMP get_ResourceResolvers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolvers** value);
        IFACEMETHODIMP get_OverrideStyles(_COM_Outptr_ ABI::Windows::UI::Xaml::IResourceDictionary** overrideDictionary);
        IFACEMETHODIMP AddError(_In_ ABI::AdaptiveCards::Uwp::ErrorStatusCode statusCode, _In_ HSTRING message);
        IFACEMETHODIMP AddWarning(_In_ ABI::AdaptiveCards::Uwp::WarningStatusCode statusCode, _In_ HSTRING message);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::RenderedAdaptiveCard> m_renderResult;
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::AdaptiveActionInvoker> m_actionInvoker;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolvers> m_resourceResolvers;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_overrideDictionary;
    };

    ActivatableClass(AdaptiveRenderContext);
}}
