// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveTextStyleConfigBase
    {
        AdaptiveTextStyleConfigBase(::AdaptiveCards::TextStyleConfig const& textStyleConfig);

        property<ObjectModel::WinUI3::TextWeight> Weight;
        property<ObjectModel::WinUI3::TextSize> Size;
        property<ObjectModel::WinUI3::ForegroundColor> Color;
        property<bool> IsSubtle;
        property<ObjectModel::WinUI3::FontType> FontType;

    };
}
