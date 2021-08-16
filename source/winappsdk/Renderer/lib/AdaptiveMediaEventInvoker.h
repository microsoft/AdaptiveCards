// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveMediaEventInvoker
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveMediaEventInvoker>
    {
        AdaptiveRuntime(AdaptiveMediaEventInvoker);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendMediaClickedEvent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia* mediaElement);

    private:
        Microsoft::WRL::WeakRef m_weakRenderResult;
    };

    ActivatableClass(AdaptiveMediaEventInvoker);
}
