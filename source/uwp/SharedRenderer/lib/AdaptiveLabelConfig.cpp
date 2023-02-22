// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveLabelConfig.h"
#include "AdaptiveLabelConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveLabelConfig::AdaptiveLabelConfig(::AdaptiveCards::LabelConfig const& labelConfig) :
        InputSpacing{static_cast<winrt::Spacing>(labelConfig.inputSpacing)},
        RequiredInputs{winrt::make<implementation::AdaptiveInputLabelConfig>(labelConfig.requiredInputs)},
        OptionalInputs{winrt::make<implementation::AdaptiveInputLabelConfig>(labelConfig.optionalInputs)}
    {
    }
}
