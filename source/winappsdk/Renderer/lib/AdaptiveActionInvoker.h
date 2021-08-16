// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveActionInvoker
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionInvoker>
    {
        AdaptiveRuntime(AdaptiveActionInvoker);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendActionEvent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* actionElement);

    private:
        Microsoft::WRL::WeakRef m_weakRenderResult;
    };

    ActivatableClass(AdaptiveActionInvoker);
}
