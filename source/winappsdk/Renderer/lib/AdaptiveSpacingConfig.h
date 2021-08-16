// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveSpacingConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveSpacingConfig : AdaptiveSpacingConfigT<AdaptiveSpacingConfig>
    {
        AdaptiveSpacingConfig(::AdaptiveCards::SpacingConfig const& SpacingConfig = {});

        property<uint32_t> Small;
        property<uint32_t> Default;
        property<uint32_t> Medium;
        property<uint32_t> Large;
        property<uint32_t> ExtraLarge;
        property<uint32_t> Padding;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveSpacingConfig : AdaptiveSpacingConfigT<AdaptiveSpacingConfig, implementation::AdaptiveSpacingConfig>
    {
    };
}
