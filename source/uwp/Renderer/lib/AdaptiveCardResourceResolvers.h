// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCardResourceResolvers.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveCardResourceResolvers : AdaptiveCardResourceResolversT<AdaptiveCardResourceResolvers>
    {
        AdaptiveCardResourceResolvers() = default;

        void Set(hstring const& scheme, winrt::IAdaptiveCardResourceResolver const& resolver);
        Uwp::IAdaptiveCardResourceResolver Get(hstring const& scheme);

        std::map<hstring, Rendering::Uwp::IAdaptiveCardResourceResolver> m_resourceResolvers;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveCardResourceResolvers
        : AdaptiveCardResourceResolversT<AdaptiveCardResourceResolvers, implementation::AdaptiveCardResourceResolvers>
    {
    };
}
