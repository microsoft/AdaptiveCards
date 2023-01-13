// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSpacingConfig.h"
#include "AdaptiveSpacingConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
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
