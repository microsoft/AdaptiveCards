// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveInputLabelConfig.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveLabelConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveLabelConfig>
    {
        AdaptiveRuntime(AdaptiveLabelConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(LabelConfig labelConfig) noexcept;

        IFACEMETHODIMP get_InputSpacing(_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing* spacing);
        IFACEMETHODIMP put_InputSpacing(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing spacing);

        IFACEMETHODIMP get_RequiredInputs(_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputLabelConfig** requiredInputs);
        IFACEMETHODIMP put_RequiredInputs(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputLabelConfig* requiredInputs);

        IFACEMETHODIMP get_OptionalInputs(_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputLabelConfig** optionalInputs);
        IFACEMETHODIMP put_OptionalInputs(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputLabelConfig* optionalInputs);

    private:
        ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing m_inputSpacing;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputLabelConfig> m_requiredInputs;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputLabelConfig> m_optionalInputs;
    };
    ActivatableClass(AdaptiveLabelConfig);
}
