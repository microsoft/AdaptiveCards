// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputLabelConfig.h"
#include "AdaptiveInputLabelConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveInputLabelConfig::AdaptiveInputLabelConfig(::AdaptiveCards::InputLabelConfig const& inputLabelConfig)
    {
        Color = static_cast<ObjectModel::Uwp::ForegroundColor>(inputLabelConfig.color);
        IsSubtle = inputLabelConfig.isSubtle;
        Size = static_cast<ObjectModel::Uwp::TextSize>(inputLabelConfig.size);
        Suffix = UTF8ToHString(inputLabelConfig.suffix);
        Weight = static_cast<ObjectModel::Uwp::TextWeight>(inputLabelConfig.weight);
    }
}
