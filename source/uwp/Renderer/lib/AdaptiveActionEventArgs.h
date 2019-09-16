// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveActionEventArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>, ABI::AdaptiveNamespace::IAdaptiveActionEventArgs>
    {
        AdaptiveRuntime(AdaptiveActionEventArgs);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveInputs* inputs);

        // IAdaptiveActionEventArgs
        IFACEMETHODIMP get_Action(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action);
        IFACEMETHODIMP get_Inputs(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputs** inputs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_action;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputs> m_inputs;
    };
}
