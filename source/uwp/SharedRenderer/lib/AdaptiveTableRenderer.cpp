// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTableRenderer.h"
#include "AdaptiveTableRenderer.g.cpp"
#include "WholeItemsPanel.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::FrameworkElement AdaptiveTableRenderer::RenderCell(winrt::AdaptiveTableCell const& cell,
                                                              winrt::AdaptiveRenderContext const& renderContext,
                                                              winrt::AdaptiveRenderArgs const& renderArgs,
                                                              winrt::IReference<winrt::VerticalContentAlignment> const& verticalContentAlignment,
                                                              boolean showGridLines,
                                                              winrt::ContainerStyle gridStyle,
                                                              uint32_t rowNumber,
                                                              uint32_t columnNumber)
    {
        auto cellVerticalAlignment = cell.VerticalContentAlignment();
        // If the cell doesn't have a vertical content alignment, pass in the one from the parent
        if (cellVerticalAlignment == nullptr)
        {
            cell.VerticalContentAlignment(verticalContentAlignment);
        }

        if (showGridLines)
        {
            // If we're showing grid lines add padding so the content isn't against the grid
            renderArgs.AddContainerPadding(true);
        }

        // Render the cell as a container
        auto containerRenderer = renderContext.ElementRenderers().Get(L"Container");

        auto cellRenderedAsContainer = containerRenderer.Render(cell, renderContext, renderArgs);

        // Handle Grid Lines or Cell Spacing
        auto hostConfig = renderContext.HostConfig();

        winrt::FrameworkElement cellFrameworkElement{nullptr};
        if (showGridLines)
        {
            // If we're showing grid lines put the cell in a border
            winrt::Border cellBorder{};

            auto borderColor = GetBorderColorFromStyle(gridStyle, hostConfig);
            cellBorder.BorderBrush(winrt::SolidColorBrush{borderColor});

            // Create a border around the cell. Only set the top or left borders if we're in the top or leftmost
            // cells respectively in order to avoid double-thickness borders
            winrt::Thickness borderThickness = {0, 0, 1, 1};
            if (columnNumber == 0)
            {
                borderThickness.Left = 1;
            }
            if (rowNumber == 0)
            {
                borderThickness.Top = 1;
            }

            cellBorder.BorderThickness(borderThickness);
            cellBorder.Child(cellRenderedAsContainer);
            cellFrameworkElement = cellBorder;
            // Clear the container padding flag from the renderArgs
            renderArgs.AddContainerPadding(false);
        }
        else
        {
            // If we're not showing gridlines, use the rendered cell as the frameworkElement, and add the cell spacing
            cellFrameworkElement = cellRenderedAsContainer.as<winrt::FrameworkElement>();

            auto tableConfig = hostConfig.Table();

            double cellSpacingDouble = static_cast<double>(tableConfig.CellSpacing());
            if (cellSpacingDouble != 0)
            {
                // Set left and top margin for each cell (to avoid double margins). Don't set the margin on topmost
                // or leftmost cells to avoid creating margin outside the table.
                winrt::Thickness marginThickness = {cellSpacingDouble, cellSpacingDouble, 0, 0};
                if (columnNumber == 0)
                {
                    marginThickness.Left = 0;
                }
                if (rowNumber == 0)
                {
                    marginThickness.Top = 0;
                }
                if (marginThickness.Left != 0 || marginThickness.Top != 0)
                {
                    cellFrameworkElement.Margin(marginThickness);
                }
            }
        }

        // If the cell didn't have a vertical content alignment when we started, set it back to null
        if (cellVerticalAlignment == nullptr)
        {
            cell.VerticalContentAlignment(nullptr);
        }

        return cellFrameworkElement;
    }

    void AdaptiveTableRenderer::RenderRow(winrt::AdaptiveTableRow const& row,
                                          winrt::IVector<winrt::AdaptiveTableColumnDefinition> const& columns,
                                          winrt::AdaptiveRenderContext const& renderContext,
                                          winrt::AdaptiveRenderArgs const& renderArgs,
                                          winrt::IReference<winrt::VerticalContentAlignment> const& verticalContentAlignment,
                                          boolean firstRowAsHeaders,
                                          boolean showGridLines,
                                          winrt::ContainerStyle gridStyle,
                                          uint32_t rowNumber,
                                          winrt::Grid const& xamlGrid)
    {
        // Create the row definition and add it to the grid
        winrt::RowDefinition xamlRowDefinition{};

        xamlGrid.RowDefinitions().Append(xamlRowDefinition);

        // Save the current text style
        auto contextTextStyle = renderContext.TextStyle();

        // Set the column header style if this is the first row and firstRowAsHeaders is set
        if (rowNumber == 0 && firstRowAsHeaders)
        {
            // Set the text style to TextStyle::ColumnHeader
            renderContext.TextStyle(winrt::TextStyle::ColumnHeader);
        }

        // Save the current horizontal alignment from the context
        auto contextHorizontalAlignment = renderContext.HorizontalContentAlignment();

        // Get the horizontal alignment for this row
        auto rowHorizontalAlignment = row.HorizontalCellContentAlignment();

        // Get the vertical alignemnt for this row
        auto rowVerticalContentAlignment = row.VerticalCellContentAlignment();

        // If there's no row vertical alignment, use the passed in value
        if (!rowVerticalContentAlignment)
        {
            rowVerticalContentAlignment = verticalContentAlignment;
        }

        // Create the cells
        auto cells = row.Cells();

        uint32_t columnNumber = 0;

        for (auto cell : cells)
        {
            // Get the horizontal alignment from the column definition
            auto columnDefinition = columns.GetAt(columnNumber);
            auto columnHorizontalAlignment = columnDefinition.HorizontalCellContentAlignment();

            // Use row if present, then column, then table (which was passed in from the context)
            if (rowHorizontalAlignment)
            {
                renderContext.HorizontalContentAlignment(rowHorizontalAlignment);
            }
            else
            {
                renderContext.HorizontalContentAlignment(columnHorizontalAlignment ? columnHorizontalAlignment :
                                                                                     contextHorizontalAlignment);
            }

            // Render the cell
            auto cellFrameworkElement =
                RenderCell(cell, renderContext, renderArgs, rowVerticalContentAlignment, showGridLines, gridStyle, rowNumber, columnNumber);

            // Set the row and column numbers on the cell
            winrt::Grid::SetColumn(cellFrameworkElement, columnNumber);
            winrt::Grid::SetRow(cellFrameworkElement, rowNumber);

            // Add the cell to the panel
            XamlHelpers::AppendXamlElementToPanel(cellFrameworkElement, xamlGrid);
            columnNumber++;
        }

        // Reset the render context to its original values
        renderContext.TextStyle(contextTextStyle);
        renderContext.HorizontalContentAlignment(contextHorizontalAlignment);
    }

    winrt::UIElement AdaptiveTableRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveTable = cardElement.as<winrt::AdaptiveTable>();

            // Create a grid to represent the table
            winrt::Grid xamlGrid{};

            // Get the vertical content alignment from the table
            auto tableHorizontalAlignment = adaptiveTable.HorizontalCellContentAlignment();

            // Save the current horizontal content alignment from the context, and replace it with the one
            // from the table if present
            auto contextHorizontalAlignment = renderContext.HorizontalContentAlignment();
            if (tableHorizontalAlignment)
            {
                renderContext.HorizontalContentAlignment(tableHorizontalAlignment);
            }

            auto tableVerticalAlignment = adaptiveTable.VerticalCellContentAlignment();
            bool showGridLines = adaptiveTable.ShowGridLines();

            // Create the column definitions
            auto columns = adaptiveTable.Columns();
            auto xamlColumnDefinitions = xamlGrid.ColumnDefinitions();

            for (auto column : columns)
            {
                winrt::ColumnDefinition xamlColumnDefinition{};
                XamlHelpers::HandleTableColumnWidth(column, xamlColumnDefinition);
                xamlColumnDefinitions.Append(xamlColumnDefinition);
            }

            // Create the rows
            auto rows = adaptiveTable.Rows();

            bool firstRowAsHeaders = adaptiveTable.FirstRowAsHeaders();

            auto gridStyle = adaptiveTable.GridStyle();

            uint32_t rowNumber = 0;
            for (auto row : rows)
            {
                RenderRow(row, columns, renderContext, renderArgs, tableVerticalAlignment, firstRowAsHeaders, showGridLines, gridStyle, rowNumber, xamlGrid);

                rowNumber++;
            }

            // Reset the render context to its original horizontal content alignemnt value
            renderContext.HorizontalContentAlignment(contextHorizontalAlignment);
            return xamlGrid;
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
