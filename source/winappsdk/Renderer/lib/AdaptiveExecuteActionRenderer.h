// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveExecuteActionRenderer
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionRenderer>
    {
        AdaptiveRuntime(AdaptiveExecuteActionRenderer);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Render(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                              _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result) noexcept override;
    };

    ActivatableClass(AdaptiveExecuteActionRenderer);
}
