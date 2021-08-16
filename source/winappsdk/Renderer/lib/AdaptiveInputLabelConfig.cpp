// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputLabelConfig.h"
#include "AdaptiveInputLabelConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveInputLabelConfig::AdaptiveInputLabelConfig(::AdaptiveCards::InputLabelConfig inputLabelConfig)
    {
        Color = static_cast<ObjectModel::WinUI3::ForegroundColor>(inputLabelConfig.color);
        IsSubtle = inputLabelConfig.isSubtle;
        Size = static_cast<ObjectModel::WinUI3::TextSize>(inputLabelConfig.size);
        Suffix = UTF8ToHString(inputLabelConfig.suffix);
        Weight = static_cast<ObjectModel::WinUI3::TextWeight>(inputLabelConfig.weight);
    }
}
