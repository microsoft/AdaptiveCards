// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveRenderArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveRenderArgs : AdaptiveRenderArgsT<AdaptiveRenderArgs>
    {
        AdaptiveRenderArgs() = default;

        AdaptiveRenderArgs(winrt::ContainerStyle const& containerStyle,
                           winrt::IInspectable const& parentElement,
                           Uwp::AdaptiveRenderArgs const& renderArgs);

        AdaptiveRenderArgs(winrt::ContainerStyle const& containerStyle,
                           winrt::IInspectable const& parentElement,
                           winrt::AdaptiveCard const& parentCard,
                           Uwp::AdaptiveRenderArgs const& renderArgs);

        property<winrt::ContainerStyle> ContainerStyle;
        property<winrt::IInspectable> ParentElement;
        property<winrt::AdaptiveCard> ParentCard;
        property<bool> IsInShowCard{false};
        property<bool> AllowAboveTitleIconPlacement{false};
        property<bool> AncestorHasFallback{false};
        property<bool> AddContainerPadding{false};
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveRenderArgs : AdaptiveRenderArgsT<AdaptiveRenderArgs, implementation::AdaptiveRenderArgs>
    {
    };
}
