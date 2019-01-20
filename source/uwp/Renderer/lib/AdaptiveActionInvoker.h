#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveNamespace
{
    class AdaptiveActionInvoker
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveActionInvoker>
    {
        AdaptiveRuntime(AdaptiveActionInvoker);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ AdaptiveNamespace::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendActionEvent(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* actionElement);

    private:
        Microsoft::WRL::ComPtr<AdaptiveNamespace::RenderedAdaptiveCard> m_renderResult;
    };

    ActivatableClass(AdaptiveActionInvoker);
}
