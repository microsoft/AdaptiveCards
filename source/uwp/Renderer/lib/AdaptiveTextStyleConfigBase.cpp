// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextStyleConfigBase.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveTextStyleConfigBase::AdaptiveTextStyleConfigBase(::AdaptiveCards::TextStyleConfig const& textStyleConfig)
    {
        Weight = static_cast<ObjectModel::Uwp::TextWeight>(textStyleConfig.weight);
        Size = static_cast<ObjectModel::Uwp::TextSize>(textStyleConfig.size);
        Color = static_cast<ObjectModel::Uwp::ForegroundColor>(textStyleConfig.color);
        IsSubtle = textStyleConfig.isSubtle;
        FontType = static_cast<ObjectModel::Uwp::FontType>(textStyleConfig.fontType);
    }
}
