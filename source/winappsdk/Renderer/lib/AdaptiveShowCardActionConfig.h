// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveShowCardActionConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveShowCardActionConfig : AdaptiveShowCardActionConfigT < AdaptiveShowCardActionConfig>
    {
        AdaptiveShowCardActionConfig(::AdaptiveCards::ShowCardActionConfig const& showCardActionConfig = {});

        property<WinUI3::ActionMode> ActionMode;
        property<ObjectModel::WinUI3::ContainerStyle> Style;
        property<uint32_t> InlineTopMargin;

        IFACEMETHODIMP get_InlineTopMargin(_Out_ UINT32* value);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveShowCardActionConfig
        : AdaptiveShowCardActionConfigT<AdaptiveShowCardActionConfig, implementation::AdaptiveShowCardActionConfig>
    {
    };
}
