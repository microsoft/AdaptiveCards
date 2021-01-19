// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveLabelConfig.h"
#include "AdaptiveErrorMessageConfig.h"

namespace AdaptiveNamespace
{
    class AdaptiveInputsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveInputsConfig>
    {
        AdaptiveRuntime(AdaptiveInputsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(InputsConfig inputsConfig) noexcept;

        IFACEMETHODIMP get_ErrorMessage(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveErrorMessageConfig** errorMessage);
        IFACEMETHODIMP put_ErrorMessage(_In_ ABI::AdaptiveNamespace::IAdaptiveErrorMessageConfig* errorMessage);

        IFACEMETHODIMP get_Label(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveLabelConfig** inputLabels);
        IFACEMETHODIMP put_Label(_In_ ABI::AdaptiveNamespace::IAdaptiveLabelConfig* inputLabels);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveLabelConfig> m_label;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveErrorMessageConfig> m_errorMessage;
    };
    ActivatableClass(AdaptiveInputsConfig);
}
