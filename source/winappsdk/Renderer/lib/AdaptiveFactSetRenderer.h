// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveFactSetRenderer.g.h"

// TODO: Do we need this import here?
#include "FactSet.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{

    // TODO: have FactRenderer in .idl but no implementation for it, is that expected?
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
