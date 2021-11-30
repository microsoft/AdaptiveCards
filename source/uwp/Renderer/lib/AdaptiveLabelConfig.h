// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveInputLabelConfig.h"
#include "AdaptiveLabelConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveLabelConfig : AdaptiveLabelConfigT<AdaptiveLabelConfig>
    {
        AdaptiveLabelConfig(::AdaptiveCards::LabelConfig const& labelConfig = {});

        property<ObjectModel::Uwp::Spacing> InputSpacing;
        property<Uwp::AdaptiveInputLabelConfig> RequiredInputs;
        property<Uwp::AdaptiveInputLabelConfig> OptionalInputs;
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveLabelConfig : AdaptiveLabelConfigT<AdaptiveLabelConfig, implementation::AdaptiveLabelConfig>
    {
    };
}
