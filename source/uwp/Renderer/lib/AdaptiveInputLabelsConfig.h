// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveInputLabelConfig.h"

namespace AdaptiveNamespace
{
    class AdaptiveInputLabelsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveInputLabelsConfig>
    {
        AdaptiveRuntime(AdaptiveInputLabelsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(InputLabelsConfig inputLabelsConfig) noexcept;

        IFACEMETHODIMP get_RequiredInputs(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig** requiredInputs);
        IFACEMETHODIMP put_RequiredInputs(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig* requiredInputs);

        IFACEMETHODIMP get_OptionalInputs(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig** optionalInputs);
        IFACEMETHODIMP put_OptionalInputs(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig* optionalInputs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig> m_requiredInputs;
        Microsoft::WRL::ComPtr < ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig> m_optionalInputs;

    };
    ActivatableClass(AdaptiveInputLabelsConfig);
}
