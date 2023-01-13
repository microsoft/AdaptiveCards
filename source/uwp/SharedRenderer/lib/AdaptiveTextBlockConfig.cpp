// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlockConfig.h"
#include "AdaptiveTextBlockConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveTextBlockConfig::AdaptiveTextBlockConfig(::AdaptiveCards::TextBlockConfig const& textBlockConfig)
    {
        HeadingLevel = textBlockConfig.headingLevel;
    }
}
