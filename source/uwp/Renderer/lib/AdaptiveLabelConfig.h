// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveInputLabelConfig.h"

namespace AdaptiveNamespace
{
    class AdaptiveLabelConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveLabelConfig>
    {
        AdaptiveRuntime(AdaptiveLabelConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(LabelConfig labelConfig) noexcept;

        IFACEMETHODIMP get_InputSpacing(_Outptr_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_InputSpacing(_In_ ABI::AdaptiveNamespace::Spacing spacing);

        IFACEMETHODIMP get_RequiredInputs(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig** requiredInputs);
        IFACEMETHODIMP put_RequiredInputs(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig* requiredInputs);

        IFACEMETHODIMP get_OptionalInputs(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig** optionalInputs);
        IFACEMETHODIMP put_OptionalInputs(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig* optionalInputs);

    private:
        ABI::AdaptiveNamespace::Spacing m_inputSpacing;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig> m_requiredInputs;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig> m_optionalInputs;

    };
    ActivatableClass(AdaptiveLabelConfig);
}
