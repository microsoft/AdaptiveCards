// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveRenderArgs.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveRenderArgs : AdaptiveRenderArgsT<AdaptiveRenderArgs>
    {
        AdaptiveRenderArgs() = default;

        AdaptiveRenderArgs(ObjectModel::Uwp::ContainerStyle const& containerStyle,
                           winrt::Windows::Foundation::IInspectable const& parentElement,
                           Uwp::AdaptiveRenderArgs const& renderArgs);

        AdaptiveRenderArgs(ObjectModel::Uwp::ContainerStyle const& containerStyle,
                           winrt::Windows::Foundation::IInspectable const& parentElement,
                           ObjectModel::Uwp::AdaptiveCard const& parentCard,
                           Uwp::AdaptiveRenderArgs const& renderArgs);

        property<ObjectModel::Uwp::ContainerStyle> ContainerStyle;
        property<winrt::Windows::Foundation::IInspectable> ParentElement;
        property<ObjectModel::Uwp::AdaptiveCard> ParentCard;
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
