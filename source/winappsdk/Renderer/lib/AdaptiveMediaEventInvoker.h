// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveMediaEventInvoker
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaEventInvoker>
    {
        AdaptiveRuntime(AdaptiveMediaEventInvoker);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendMediaClickedEvent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia* mediaElement);

    private:
        Microsoft::WRL::WeakRef m_weakRenderResult;
    };

    ActivatableClass(AdaptiveMediaEventInvoker);
}
