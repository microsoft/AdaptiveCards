// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveLabelConfig.h"
#include "AdaptiveErrorMessageConfig.h"
#include "AdaptiveInputsConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveInputsConfig : AdaptiveInputsConfigT < AdaptiveInputsConfig>
    {
        AdaptiveInputsConfig(::AdaptiveCards::InputsConfig inputsConfig = {});

        property<WinUI3::AdaptiveErrorMessageConfig> ErrorMessage;
        property<WinUI3::AdaptiveLabelConfig> Label;
        // TODO: reiterate on this. Do we only need a setter or getter, or both? when we don't get {get; set;} in IDL - do we assume both getter and setter required?
        //IFACEMETHODIMP put_ErrorMessage(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveErrorMessageConfig* errorMessage);
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveInputsConfig : AdaptiveInputsConfigT<AdaptiveInputsConfig, implementation::AdaptiveInputsConfig>
    {
    };
}
