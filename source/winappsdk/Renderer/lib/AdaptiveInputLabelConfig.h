// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveInputLabelConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveInputLabelConfig : AdaptiveInputLabelConfigT < AdaptiveInputLabelConfig>
    {
        AdaptiveInputLabelConfig(::AdaptiveCards::InputLabelConfig inputLabelConfig = {});

        property<winrt::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor> Color;
        property<bool> IsSubtle;
        property<winrt::AdaptiveCards::ObjectModel::WinUI3::TextSize> Size;
        property<hstring> Suffix;
        property<winrt::AdaptiveCards::ObjectModel::WinUI3::TextWeight> Weight;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveInputLabelConfig : AdaptiveInputLabelConfigT<AdaptiveInputLabelConfig, implementation::AdaptiveInputLabelConfig>
    {
    };
}
