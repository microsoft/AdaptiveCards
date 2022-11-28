// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardResourceResolvers.h"
#include "AdaptiveCardResourceResolvers.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    void AdaptiveCardResourceResolvers::Set(hstring const& scheme, winrt::render_xaml::IAdaptiveCardResourceResolver const& resolver)
    {
        m_resourceResolvers[scheme] = resolver;
    }

    winrt::render_xaml::IAdaptiveCardResourceResolver AdaptiveCardResourceResolvers::Get(hstring const& scheme)
    {
        auto found = m_resourceResolvers.find(scheme);
        if (found != m_resourceResolvers.end())
        {
            return found->second;
        }
        else
        {
            return nullptr;
        }
    }
}
