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
            AdaptiveCards::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig** value);
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration** value);
        IFACEMETHODIMP get_ActionInvoker(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionInvoker** value);
        IFACEMETHODIMP AddInputItem(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* cardElement, _In_ ABI::Windows::UI::Xaml::IUIElement* uiElement);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::RenderedAdaptiveCard> m_renderResult;
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::AdaptiveActionInvoker> m_actionInvoker;
    };

    ActivatableClass(AdaptiveRenderContext);
}}
