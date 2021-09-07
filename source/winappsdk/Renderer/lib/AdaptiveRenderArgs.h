// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveRenderArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveRenderArgs : AdaptiveRenderArgsT<AdaptiveRenderArgs>
    {
        AdaptiveRenderArgs() = default;

        AdaptiveRenderArgs(ObjectModel::WinUI3::ContainerStyle const& containerStyle,
                           winrt::Windows::Foundation::IInspectable const& parentElement,
                           WinUI3::AdaptiveRenderArgs const& renderArgs);

        AdaptiveRenderArgs(ObjectModel::WinUI3::ContainerStyle const& containerStyle,
                           winrt::Windows::Foundation::IInspectable const& parentElement,
                           ObjectModel::WinUI3::AdaptiveCard const& parentCard,
                           WinUI3::AdaptiveRenderArgs const& renderArgs);

        property<ObjectModel::WinUI3::ContainerStyle> ContainerStyle;
        property<winrt::Windows::Foundation::IInspectable> ParentElement;
        property<ObjectModel::WinUI3::AdaptiveCard> ParentCard;
        property<bool> IsInShowCard{false};
        property<bool> AllowAboveTitleIconPlacement{false};
        property<bool> AncestorHasFallback{false};
        property<bool> AddContainerPadding{false};
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveRenderArgs : AdaptiveRenderArgsT<AdaptiveRenderArgs, implementation::AdaptiveRenderArgs>
    {
    };
}
