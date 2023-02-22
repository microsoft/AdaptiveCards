// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveLabelConfig.h"
#include "AdaptiveErrorMessageConfig.h"
#include "AdaptiveInputsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveInputsConfig : AdaptiveInputsConfigT<AdaptiveInputsConfig>
    {
        AdaptiveInputsConfig(::AdaptiveCards::InputsConfig const& inputsConfig = {});

        property<winrt::AdaptiveErrorMessageConfig> ErrorMessage;
        property<winrt::AdaptiveLabelConfig> Label;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveInputsConfig : AdaptiveInputsConfigT<AdaptiveInputsConfig, implementation::AdaptiveInputsConfig>
    {
    };
}
