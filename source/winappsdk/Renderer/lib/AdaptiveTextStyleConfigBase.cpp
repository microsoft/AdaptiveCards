// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextStyleConfigBase.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveTextStyleConfigBase::AdaptiveTextStyleConfigBase(::AdaptiveCards::TextStyleConfig const& textStyleConfig)
    {
        Weight = static_cast<ObjectModel::WinUI3::TextWeight>(textStyleConfig.weight);
        Size = static_cast<ObjectModel::WinUI3::TextSize>(textStyleConfig.size);
        Color = static_cast<ObjectModel::WinUI3::ForegroundColor>(textStyleConfig.color);
        IsSubtle = textStyleConfig.isSubtle;
        FontType = static_cast<ObjectModel::WinUI3::FontType>(textStyleConfig.fontType);
    }
}
