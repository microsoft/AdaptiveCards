// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveTableRenderer.g.h"
// TODO: do we need this here?
//#include "Table.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveTableRenderer : AdaptiveTableRendererT<AdaptiveTableRenderer>
    {
    public:
        AdaptiveTableRenderer() = default;

        winrt::Windows::UI::Xaml::UIElement Render(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    private:

        winrt::Windows::UI::Xaml::FrameworkElement RenderCell(
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableCell const& cell,
            winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
            winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
            winrt::Windows::Foundation::IReference<winrt::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment> const& verticalContentAlignment,
            boolean showGridLines,
            winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle gridStyle,
            uint32_t rowNumber,
            uint32_t columnNumber);

        void RenderRow(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableRow const& row,
                       winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableColumnDefinition> const& columns,
                       winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                       winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                       winrt::Windows::Foundation::IReference<winrt::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment> const& verticalContentAlignment,
                       boolean firstRowAsHeaders,
                       boolean showGridLines,
                       winrt::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle gridStyle,
                       uint32_t rowNumber,
                       winrt::Windows::UI::Xaml::Controls::Grid const& xamlGrid);
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveTableRenderer : AdaptiveTableRendererT<AdaptiveTableRenderer, implementation::AdaptiveTableRenderer>
    {
    };
}
