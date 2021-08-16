// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveShowCardActionConfig.h"
#include "AdaptiveShowCardActionConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveShowCardActionConfig::AdaptiveShowCardActionConfig(::AdaptiveCards::ShowCardActionConfig const& sharedShowCardActionConfig)
    {
        ActionMode = static_cast<WinUI3::ActionMode>(sharedShowCardActionConfig.actionMode);
        Style = static_cast<ObjectModel::WinUI3::ContainerStyle>(sharedShowCardActionConfig.style);
        InlineTopMargin = sharedShowCardActionConfig.inlineTopMargin;
    }
}
