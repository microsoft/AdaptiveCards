// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTableRenderer.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveTableRenderer : AdaptiveTableRendererT<AdaptiveTableRenderer>
    {
    public:
        AdaptiveTableRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    private:
        winrt::Windows::UI::Xaml::FrameworkElement RenderCell(
            winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableCell const& cell,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
            winrt::Windows::Foundation::IReference<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment> const& verticalContentAlignment,
            boolean showGridLines,
            winrt::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle,
            uint32_t rowNumber,
            uint32_t columnNumber);

        void RenderRow(winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableRow const& row,
                       winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableColumnDefinition> const& columns,
                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                       winrt::Windows::Foundation::IReference<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment> const& verticalContentAlignment,
                       boolean firstRowAsHeaders,
                       boolean showGridLines,
                       winrt::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle,
                       uint32_t rowNumber,
                       winrt::Windows::UI::Xaml::Controls::Grid const& xamlGrid);
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveTableRenderer : AdaptiveTableRendererT<AdaptiveTableRenderer, implementation::AdaptiveTableRenderer>
    {
    };
}
