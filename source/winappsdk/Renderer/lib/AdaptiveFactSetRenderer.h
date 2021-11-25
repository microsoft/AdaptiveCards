// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFactSetRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{

    // TODO: have FactRenderer in .idl but no implementation for it, is that expected? I don't think we need it
    // TODO: I didn't find it possible to declare a single fact without wrapping into FactSet according to https://adaptivecards.io/explorer/Fact.html
    struct AdaptiveFactSetRenderer : AdaptiveFactSetRendererT<AdaptiveFactSetRenderer>
    {
        AdaptiveFactSetRenderer() = default;

        Windows::UI::Xaml::UIElement Render(AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                            AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                            AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveFactSetRenderer : AdaptiveFactSetRendererT<AdaptiveFactSetRenderer, implementation::AdaptiveFactSetRenderer>
    {
    };
}
