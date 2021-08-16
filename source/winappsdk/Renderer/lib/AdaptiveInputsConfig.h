// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveLabelConfig.h"
#include "AdaptiveErrorMessageConfig.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveInputsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputsConfig>
    {
        AdaptiveRuntime(AdaptiveInputsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(InputsConfig inputsConfig) noexcept;

        IFACEMETHODIMP get_ErrorMessage(_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveErrorMessageConfig** errorMessage);
        IFACEMETHODIMP put_ErrorMessage(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveErrorMessageConfig* errorMessage);

        IFACEMETHODIMP get_Label(_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveLabelConfig** inputLabels);
        IFACEMETHODIMP put_Label(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveLabelConfig* inputLabels);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveLabelConfig> m_label;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveErrorMessageConfig> m_errorMessage;
    };
    ActivatableClass(AdaptiveInputsConfig);
}
