// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardResourceResolvers.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveCardResourceResolvers : AdaptiveCardResourceResolversT<AdaptiveCardResourceResolvers>
    {
        AdaptiveCardResourceResolvers() = default;

        void Set(hstring const& scheme, winrt::render_xaml::IAdaptiveCardResourceResolver const& resolver);
        winrt::render_xaml::IAdaptiveCardResourceResolver Get(hstring const& scheme);

        std::map<hstring, winrt::render_xaml::IAdaptiveCardResourceResolver> m_resourceResolvers;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveCardResourceResolvers
        : AdaptiveCardResourceResolversT<AdaptiveCardResourceResolvers, implementation::AdaptiveCardResourceResolvers>
    {
    };
}
