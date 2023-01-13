// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTableRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveTableRenderer : AdaptiveTableRendererT<AdaptiveTableRenderer>
    {
    public:
        AdaptiveTableRenderer() = default;

        winrt::UIElement Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::FrameworkElement RenderCell(winrt::AdaptiveTableCell const& cell,
                                                              winrt::AdaptiveRenderContext const& renderContext,
                                                              winrt::AdaptiveRenderArgs const& renderArgs,
                                                              winrt::IReference<winrt::VerticalContentAlignment> const& verticalContentAlignment,
                                                              boolean showGridLines,
                                                              winrt::ContainerStyle gridStyle,
                                                              uint32_t rowNumber,
                                                              uint32_t columnNumber);

        void RenderRow(winrt::AdaptiveTableRow const& row,
                       winrt::IVector<winrt::AdaptiveTableColumnDefinition> const& columns,
                       winrt::AdaptiveRenderContext const& renderContext,
                       winrt::AdaptiveRenderArgs const& renderArgs,
                       winrt::IReference<winrt::VerticalContentAlignment> const& verticalContentAlignment,
                       boolean firstRowAsHeaders,
                       boolean showGridLines,
                       winrt::ContainerStyle gridStyle,
                       uint32_t rowNumber,
                       winrt::Grid const& xamlGrid);
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveTableRenderer : AdaptiveTableRendererT<AdaptiveTableRenderer, implementation::AdaptiveTableRenderer>
    {
    };
}
