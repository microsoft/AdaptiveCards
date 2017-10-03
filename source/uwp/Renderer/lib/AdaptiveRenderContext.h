#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "TextBlock.h"

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
            ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration* actionRendererRegistration) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig** value);
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration** value);
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration** value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;
    };

    ActivatableClass(AdaptiveRenderContext);
}}
