// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextStyleConfigBase.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveTextStyleConfigBase::AdaptiveTextStyleConfigBase(::AdaptiveCards::TextStyleConfig const& textStyleConfig)
    {
        Weight = static_cast<winrt::TextWeight>(textStyleConfig.weight);
        Size = static_cast<winrt::TextSize>(textStyleConfig.size);
        Color = static_cast<winrt::ForegroundColor>(textStyleConfig.color);
        IsSubtle = textStyleConfig.isSubtle;
        FontType = static_cast<winrt::FontType>(textStyleConfig.fontType);
    }
}
