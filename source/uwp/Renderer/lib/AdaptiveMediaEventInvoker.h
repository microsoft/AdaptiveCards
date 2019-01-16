#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveNamespace
{
    class AdaptiveMediaEventInvoker
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveMediaEventInvoker>
    {
        AdaptiveRuntime(AdaptiveMediaEventInvoker);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ AdaptiveNamespace::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendMediaClickedEvent(_In_ ABI::AdaptiveNamespace::IAdaptiveMedia* mediaElement);

    private:
        Microsoft::WRL::ComPtr<AdaptiveNamespace::RenderedAdaptiveCard> m_renderResult;
    };

    ActivatableClass(AdaptiveMediaEventInvoker);
}
