#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveActionInvoker :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionInvoker>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveActionInvoker, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendActionEvent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* actionElement);

    private:
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard> m_renderResult;
    };

    ActivatableClass(AdaptiveActionInvoker);
}}}
