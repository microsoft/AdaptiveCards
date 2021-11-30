// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveTextStyleConfigBase
    {
        AdaptiveTextStyleConfigBase(::AdaptiveCards::TextStyleConfig const& textStyleConfig);

        property<ObjectModel::Uwp::TextWeight> Weight;
        property<ObjectModel::Uwp::TextSize> Size;
        property<ObjectModel::Uwp::ForegroundColor> Color;
        property<bool> IsSubtle;
        property<ObjectModel::Uwp::FontType> FontType;

    };
}
