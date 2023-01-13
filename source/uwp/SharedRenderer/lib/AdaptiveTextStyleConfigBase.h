// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveTextStyleConfigBase
    {
        AdaptiveTextStyleConfigBase(::AdaptiveCards::TextStyleConfig const& textStyleConfig);

        property<winrt::TextWeight> Weight;
        property<winrt::TextSize> Size;
        property<winrt::ForegroundColor> Color;
        property<bool> IsSubtle;
        property<winrt::FontType> FontType;
    };
}
