// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveInputLabelsConfig.h"
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

        IFACEMETHODIMP get_InputLabels(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelsConfig** inputLabels);
        IFACEMETHODIMP put_InputLabels(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelsConfig* inputLabels);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputLabelsConfig> m_inputLabels;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveErrorMessageConfig> m_errorMessage;
    };
    ActivatableClass(AdaptiveInputsConfig);
}
