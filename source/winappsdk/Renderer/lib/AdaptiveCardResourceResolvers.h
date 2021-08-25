// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardResourceResolvers.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveCardResourceResolvers : AdaptiveCardResourceResolversT < AdaptiveCardResourceResolvers>
    {
        AdaptiveCardResourceResolvers() = default;

        void Set(hstring const& scheme, WinUI3::IAdaptiveCardResourceResolver const& resolver);
        WinUI3::IAdaptiveCardResourceResolver Get(hstring const& scheme);

        std::map<hstring, Rendering::WinUI3::IAdaptiveCardResourceResolver> m_resourceResolvers;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveCardResourceResolvers
        : AdaptiveCardResourceResolversT<AdaptiveCardResourceResolvers, implementation::AdaptiveCardResourceResolvers>
    {
    };
}
