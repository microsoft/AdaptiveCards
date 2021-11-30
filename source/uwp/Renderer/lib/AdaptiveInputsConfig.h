// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveLabelConfig.h"
#include "AdaptiveErrorMessageConfig.h"
#include "AdaptiveInputsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveInputsConfig : AdaptiveInputsConfigT<AdaptiveInputsConfig>
    {
        AdaptiveInputsConfig(::AdaptiveCards::InputsConfig const& inputsConfig = {});

        property<Uwp::AdaptiveErrorMessageConfig> ErrorMessage;
        property<Uwp::AdaptiveLabelConfig> Label;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveInputsConfig : AdaptiveInputsConfigT<AdaptiveInputsConfig, implementation::AdaptiveInputsConfig>
    {
    };
}
