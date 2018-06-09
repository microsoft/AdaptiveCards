#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"

AdaptiveNamespaceStart
    class AdaptiveMediaEventInvoker :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveMediaEventInvoker>
    {
        AdaptiveRuntime(AdaptiveMediaEventInvoker)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(AdaptiveNamespace::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendMediaPlayEvent(_In_ ABI::AdaptiveNamespace::IAdaptiveMedia* mediaElement);
        IFACEMETHODIMP SendMediaEndedEvent(_In_ ABI::AdaptiveNamespace::IAdaptiveMedia* mediaElement);

    private:
        Microsoft::WRL::ComPtr<AdaptiveNamespace::RenderedAdaptiveCard> m_renderResult;
    };

    ActivatableClass(AdaptiveMediaEventInvoker);
AdaptiveNamespaceEnd
