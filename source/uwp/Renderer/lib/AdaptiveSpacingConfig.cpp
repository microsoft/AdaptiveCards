// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSpacingConfig.h"
#include "AdaptiveSpacingConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    // TODO: Find all the places that are constructed with an ::AdaptiveCards::Foo and ensure they take const&
    //
    // TODO: Make the .Get() methods on ::AdaptiveCards::Foo return "const&" when possible to avoid deep copies
    AdaptiveSpacingConfig::AdaptiveSpacingConfig(::AdaptiveCards::SpacingConfig const& spacingConfig)
    {
        Small = spacingConfig.smallSpacing;
        Medium = spacingConfig.mediumSpacing;
        Large = spacingConfig.largeSpacing;
        ExtraLarge = spacingConfig.extraLargeSpacing;
        Default = spacingConfig.defaultSpacing;
        Padding = spacingConfig.paddingSpacing;
    }
}
