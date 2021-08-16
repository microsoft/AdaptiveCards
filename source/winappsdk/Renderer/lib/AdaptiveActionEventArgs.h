// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.WinAppSDK.h"

namespace AdaptiveCards::Rendering::WinAppSDK
{
    class AdaptiveActionEventArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveActionEventArgs>
    {
        AdaptiveRuntime(AdaptiveActionEventArgs);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveActionElement* action,
                                       _In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveInputs* inputs);

        // IAdaptiveActionEventArgs
        IFACEMETHODIMP get_Action(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveActionElement** action);
        IFACEMETHODIMP get_Inputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveInputs** inputs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveActionElement> m_action;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveInputs> m_inputs;
    };
}
