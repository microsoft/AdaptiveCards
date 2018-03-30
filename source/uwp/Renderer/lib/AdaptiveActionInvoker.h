#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"

AdaptiveNamespaceStart
    class AdaptiveActionInvoker :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveActionInvoker>
    {
        AdaptiveRuntime(AdaptiveActionInvoker)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(AdaptiveNamespaceRef::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendActionEvent(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveActionElement* actionElement);

    private:
        Microsoft::WRL::ComPtr<AdaptiveNamespaceRef::RenderedAdaptiveCard> m_renderResult;
    };

    ActivatableClass(AdaptiveActionInvoker);
AdaptiveNamespaceEnd
