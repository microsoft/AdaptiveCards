// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputsConfig.h"
#include "AdaptiveInputsConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveInputsConfig::AdaptiveInputsConfig(::AdaptiveCards::InputsConfig inputsConfig) :
        ErrorMessage{winrt::make<implementation::AdaptiveErrorMessageConfig>(inputsConfig.errorMessage)},
        Label{winrt::make<implementation::AdaptiveLabelConfig>(inputsConfig.label)}
    {
    }
}
