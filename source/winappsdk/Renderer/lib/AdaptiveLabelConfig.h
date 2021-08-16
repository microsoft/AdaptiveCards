// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveInputLabelConfig.h"
#include "AdaptiveLabelConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveLabelConfig : AdaptiveLabelConfigT<AdaptiveLabelConfig>
    {
        AdaptiveLabelConfig(::AdaptiveCards::LabelConfig labelConfig = {});

        property<ObjectModel::WinUI3::Spacing> InputSpacing;
        property<WinUI3::AdaptiveInputLabelConfig> RequiredInputs;
        property<WinUI3::AdaptiveInputLabelConfig> OptionalInputs;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveLabelConfig : AdaptiveLabelConfigT<AdaptiveLabelConfig, implementation::AdaptiveLabelConfig>
    {
    };
}
