// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveLabelConfig.h"
#include "AdaptiveLabelConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveLabelConfig::AdaptiveLabelConfig(::AdaptiveCards::LabelConfig labelConfig) :
        InputSpacing{static_cast<ObjectModel::WinUI3::Spacing>(labelConfig.inputSpacing)},
        RequiredInputs{winrt::make<implementation::AdaptiveInputLabelConfig>(labelConfig.requiredInputs)},
        OptionalInputs{winrt::make<implementation::AdaptiveInputLabelConfig>(labelConfig.optionalInputs)}
    {
    }
}
