#pragma once

#include "AdaptiveCards.Uwp.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveActionInvoker :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveActionInvoker>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveActionInvoker, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(AdaptiveCards::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendActionEvent(ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* actionElement);

    private:
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::RenderedAdaptiveCard> m_renderResult;
    };

    ActivatableClass(AdaptiveActionInvoker);
}}
