// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
        Microsoft::WRL::WeakRef m_weakRenderResult;
    };

    ActivatableClass(AdaptiveActionInvoker);
}
