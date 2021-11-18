// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTableRenderer.h"
#include "util.h"
#include "XamlHelpers.h"

using namespace AdaptiveCards::Rendering::WinUI3::XamlHelpers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::FrameworkElement AdaptiveTableRenderer::RenderCell(rtom::AdaptiveTableCell const& cell,
                                                               rtrender::AdaptiveRenderContext const& renderContext,
                                                               rtrender::AdaptiveRenderArgs const& renderArgs,
                                                               winrt::Windows::Foundation::IReference<rtom::VerticalContentAlignment> const& verticalContentAlignment,
                                                               boolean showGridLines,
                                                               rtom::ContainerStyle gridStyle,
                                                               uint32_t rowNumber,
                                                               uint32_t columnNumber)
    {
        /* ComPtr<IAdaptiveTableCell> tableCell(cell);
         ComPtr<IAdaptiveContainer> tableCellAsContainer;
         RETURN_IF_FAILED(tableCell.As(&tableCellAsContainer));*/

        // Get the vertical content alignemnt from the cell
        /*ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>>
        cellVerticalAlignment;
        RETURN_IF_FAILED(tableCellAsContainer->get_VerticalContentAlignment(&cellVerticalAlignment));*/
        auto cellVerticalAlignment = cell.VerticalContentAlignment();

        // If the cell doesn't have a vertical content alignment, pass in the one from the parent
        if (cellVerticalAlignment == nullptr)
        {
            // RETURN_IF_FAILED(tableCellAsContainer->put_VerticalContentAlignment(verticalContentAlignment));
            cell.VerticalContentAlignment(verticalContentAlignment);
        }

        if (showGridLines)
        {
            // If we're showing grid lines add padding so the content isn't against the grid lines
            // RETURN_IF_FAILED(renderArgs->put_AddContainerPadding(true));
            renderArgs.AddContainerPadding(true);
        }

        // Render the cell as a container
        /*  ComPtr<IAdaptiveElementRendererRegistration> rendererRegistration;
          RETURN_IF_FAILED(renderContext->get_ElementRenderers(&rendererRegistration));*/
        auto rendererRegistration = renderContext.ElementRenderers();

        /* ComPtr<IAdaptiveElementRenderer> containerRenderer;
         HString containerTypeString;
         RETURN_IF_FAILED(containerTypeString.Set(L"Container"));
         RETURN_IF_FAILED(rendererRegistration->Get(containerTypeString.Get(), &containerRenderer));*/
        // winrt::hstring containerTypeString{L"Container"};
        // TODO: should be fine, right?
        auto containerRenderer = rendererRegistration.Get(L"Container");

        /*ComPtr<IAdaptiveCardElement> tableCellAsCardElement;
        RETURN_IF_FAILED(tableCell.As(&tableCellAsCardElement));*/

        /* ComPtr<IUIElement> cellRenderedAsContainer;
         RETURN_IF_FAILED(containerRenderer->Render(tableCellAsCardElement.Get(), renderContext, renderArgs, &cellRenderedAsContainer));*/
        // TODO: no need to cast cell to IAdapativeCardElement, right?
        auto cellRenderedAsContainer = containerRenderer.Render(cell, renderContext, renderArgs);
        // Handle Grid Lines or Cell Spacing
        /*ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/
        auto hostConfig = renderContext.HostConfig();

        // ComPtr<IFrameworkElement> cellFrameworkElement;
        rtxaml::FrameworkElement cellFrameworkElement{nullptr};
        if (showGridLines)
        {
            // If we're showing grid lines put the cell in a border
            /*ComPtr<IBorder> cellBorder =
                XamlHelpers::CreateABIClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

            ABI::Windows::UI::Color borderColor;
            RETURN_IF_FAILED(GetBorderColorFromStyle(gridStyle, hostConfig.Get(), &borderColor));
            RETURN_IF_FAILED(cellBorder->put_BorderBrush(XamlHelpers::GetSolidColorBrush(borderColor).Get()));*/

            rtxaml::Controls::Border cellBorder{};
            auto borderColor = GetBorderColorFromStyle(gridStyle, hostConfig);

            // Create a border around the cell. Only set the top or left borders if we're in the top or leftmost
            // cells respectively in order to avoid double-thickness borders
            rtxaml::Thickness borderThickness = {0, 0, 1, 1};
            if (columnNumber == 0)
            {
                borderThickness.Left = 1;
            }
            if (rowNumber == 0)
            {
                borderThickness.Top = 1;
            }

            /*RETURN_IF_FAILED(cellBorder->put_BorderThickness(borderThickness));

            RETURN_IF_FAILED(cellBorder->put_Child(cellRenderedAsContainer.Get()));

            RETURN_IF_FAILED(cellBorder.As(&cellFrameworkElement));*/
            cellBorder.BorderThickness(borderThickness);
            cellBorder.Child(cellRenderedAsContainer);
            cellFrameworkElement = cellBorder;
            // Clear the container padding flag from the renderArgs
            // RETURN_IF_FAILED(renderArgs->put_AddContainerPadding(false));
            // TODO: how do we know it wasn't true before? should we save and then reassign?
            renderArgs.AddContainerPadding(false);
        }
        else
        {
            // If we're not showing gridlines, use the rendered cell as the frameworkElement, and add the cell spacing
            /* RETURN_IF_FAILED(cellRenderedAsContainer.As(&cellFrameworkElement));*/
            cellFrameworkElement = cellRenderedAsContainer.as<rtxaml::FrameworkElement>();

            /*ComPtr<IAdaptiveTableConfig> tableConfig;
            RETURN_IF_FAILED(hostConfig->get_Table(&tableConfig));*/
            auto tableConfig = hostConfig.Table();

            uint32_t cellSpacing = tableConfig.CellSpacing();
            // RETURN_IF_FAILED(tableConfig->get_CellSpacing(&cellSpacing));
            double cellSpacingDouble = static_cast<double>(cellSpacing);

            // Set left and top margin for each cell (to avoid double margins). Don't set the margin on topmost
            // or leftmost cells to avoid creating margin outside the table.
            rtxaml::Thickness marginThickness = {cellSpacingDouble, cellSpacingDouble, 0, 0};
            if (columnNumber == 0)
            {
                marginThickness.Left = 0;
            }
            if (rowNumber == 0)
            {
                marginThickness.Top = 0;
            }

            // RETURN_IF_FAILED(cellFrameworkElement->put_Margin(marginThickness));
            cellFrameworkElement.Margin(marginThickness);
        }

        // If the cell didn't have a vertical content alignment when we started, set it back to null
        if (cellVerticalAlignment == nullptr)
        {
            // RETURN_IF_FAILED(tableCellAsContainer->put_VerticalContentAlignment(nullptr));
            cell.VerticalContentAlignment(nullptr);
        }

        /*RETURN_IF_FAILED(cellFrameworkElement.CopyTo(renderedCell));*/
        return cellFrameworkElement;

        // return S_OK;
    }

    void AdaptiveTableRenderer::RenderRow(rtom::AdaptiveTableRow const& row,
                                          winrt::Windows::Foundation::Collections::IVector<rtom::AdaptiveTableColumnDefinition> const& columns,
                                          rtrender::AdaptiveRenderContext const& renderContext,
                                          rtrender::AdaptiveRenderArgs const& renderArgs,
                                          winrt::Windows::Foundation::IReference<rtom::VerticalContentAlignment> const& verticalContentAlignment,
                                          boolean firstRowAsHeaders,
                                          boolean showGridLines,
                                          rtom::ContainerStyle gridStyle,
                                          uint32_t rowNumber,
                                          rtxaml::Controls::Grid const& xamlGrid)
    {
        // Create the row definition and add it to the grid
        /*ComPtr<IRowDefinition> xamlRowDefinition =
            XamlHelpers::CreateABIClass<IRowDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));*/
        rtxaml::Controls::RowDefinition xamlRowDefinition{};

        /*ComPtr<IVector<RowDefinition*>> xamlRowDefinitions;
        RETURN_IF_FAILED(xamlGrid->get_RowDefinitions(&xamlRowDefinitions));
        RETURN_IF_FAILED(xamlRowDefinitions->Append(xamlRowDefinition.Get()));*/

        auto xamlRowDefinitions = xamlGrid.RowDefinitions();
        xamlRowDefinitions.Append(xamlRowDefinition);

        // Save the current text style
        /*ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle>>
        contextTextStyle; RETURN_IF_FAILED(renderContext->get_TextStyle(&contextTextStyle));*/
        auto contextTextStyle = renderContext.TextStyle();

        // Set the column header style if this is the first row and firstRowAsHeaders is set
        if (rowNumber == 0 && firstRowAsHeaders)
        {
            // Set the text style to TextStyle::ColumnHeader
            // TODO: it will create IReference automatically, right?
            // TODO: fix firstRowAsHeader(s) variable name
            renderContext.TextStyle(rtom::TextStyle::ColumnHeader);
            /*winrt::box_value(ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle::ColumnHeader)
                .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextStyle>>()
                .get()));*/
        }

        // Save the current horizontal alignment from the context
        /* ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> contextHorizontalAlignment;
         RETURN_IF_FAILED(renderContext->get_HorizontalContentAlignment(&contextHorizontalAlignment));*/

        auto contextHorizontalAlignment = renderContext.HorizontalContentAlignment();

        // Get the horizontal alignment for this row
        // ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> rowHorizontalAlignment;
        // RETURN_IF_FAILED(row->get_HorizontalCellContentAlignment(&rowHorizontalAlignment));
        auto rowHorizontalAlignment = row.HorizontalCellContentAlignment();

        // Get the vertical alignemnt for this row
        /* ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>>
         rowVerticalContentAlignment;
         RETURN_IF_FAILED(row->get_VerticalCellContentAlignment(&rowVerticalContentAlignment));*/
        auto rowVerticalContentAlignment = row.VerticalCellContentAlignment();

        // If there's no row vertical alignment, use the passed in value
        if (rowVerticalContentAlignment == nullptr)
        {
            rowVerticalContentAlignment = verticalContentAlignment;
        }

        /* ComPtr<IGridStatics> gridStatics;
         RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));*/
        rtxaml::Controls::Grid gridStatics{};

        // Create the cells
        /*ComPtr<IVector<AdaptiveTableCell*>> cells;
        RETURN_IF_FAILED(row->get_Cells(&cells));*/
        auto cells = row.Cells();

        uint32_t columnNumber = 0;
        /*
            IterateOverVectorWithFailure<AdaptiveTableCell, IAdaptiveTableCell>(
                cells.Get(),
                true,
                [&](IAdaptiveTableCell* cell)*/
        // TODO: how do we handle errors here? do we wanna use IterOverVecWithFailure?
        for (auto cell : cells)
        {
            // Get the horizontal alignment from the column definition
            /* ComPtr<IAdaptiveTableColumnDefinition> columnDefinition;
             RETURN_IF_FAILED(columns->GetAt(columnNumber, &columnDefinition));*/
            auto columnDefinition = columns.GetAt(columnNumber);

            /*ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> columnHorizontalAlignment;
            RETURN_IF_FAILED(columnDefinition->get_HorizontalCellContentAlignment(&columnHorizontalAlignment));*/
            auto columnHorizontalAlignment = columnDefinition.HorizontalCellContentAlignment();

            // Use row if present, then column, then table (which was passed in from the context)
            if (rowHorizontalAlignment != nullptr)
            {
                renderContext.HorizontalContentAlignment(rowHorizontalAlignment);
            }
            else
            {
                // TODO: it's okay to pass the enum instead of ref, right? constructor will be invoked?
                renderContext.HorizontalContentAlignment(
                    GetValueFromRef(columnHorizontalAlignment, contextHorizontalAlignment.Value()));
            }
            /* else if (columnHorizontalAlignment != nullptr)
             {
                 RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(columnHorizontalAlignment.Get()));
             }
             else
             {
                 RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(contextHorizontalAlignment.Get()));
             }*/

            // Render the cell
            /* ComPtr<IFrameworkElement> cellFrameworkElement;
             RETURN_IF_FAILED(RenderCell(
                 cell, renderContext, renderArgs, rowVerticalContentAlignment.Get(), showGridLines, gridStyle,
             rowNumber, columnNumber, &cellFrameworkElement));*/
            auto cellFrameworkElement =
                RenderCell(cell, renderContext, renderArgs, rowVerticalContentAlignment, showGridLines, gridStyle, rowNumber, columnNumber);

            // Set the row and column numbers on the cell
            /*RETURN_IF_FAILED(gridStatics->SetColumn(cellFrameworkElement.Get(), columnNumber));
            RETURN_IF_FAILED(gridStatics->SetRow(cellFrameworkElement.Get(), rowNumber));*/
            rtxaml::Controls::Grid::SetColumn(cellFrameworkElement, columnNumber);
            rtxaml::Controls::Grid::SetColumn(cellFrameworkElement, rowNumber);

            // Add the cell to the panel
            /*ComPtr<IGrid> localXamlGrid(xamlGrid);
            ComPtr<IPanel> xamlGridAsPanel;
            RETURN_IF_FAILED(localXamlGrid.As(&xamlGridAsPanel));
            XamlHelpers::AppendXamlElementToPanel(cellFrameworkElement.Get(), xamlGridAsPanel.Get());*/
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(cellFrameworkElement, xamlGrid);

            columnNumber++;
        }

        // Reset the render context to its original values
        /* RETURN_IF_FAILED(renderContext->put_TextStyle(contextTextStyle.Get()));
         RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(contextHorizontalAlignment.Get()));*/
        renderContext.TextStyle(contextTextStyle);
        renderContext.HorizontalContentAlignment(contextHorizontalAlignment);
    }

    rtxaml::UIElement AdaptiveTableRenderer::Render(rtom::IAdaptiveCardElement const& cardElement,
                                                    rtrender::AdaptiveRenderContext const& renderContext,
                                                    rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            /*ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
            ComPtr<IAdaptiveTable> adaptiveTable;
            RETURN_IF_FAILED(cardElement.As(&adaptiveTable));*/
            auto adaptiveTable = cardElement.as<rtom::AdaptiveTable>();

            // Create a grid to represent the table
            /* ComPtr<IGrid> xamlGrid =
                 XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));*/

            rtxaml::Controls::Grid xamlGrid{};

            // Get the vertical content alignment from the table
            /* ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> tableHorizontalAlignment;
             RETURN_IF_FAILED(adaptiveTable->get_HorizontalCellContentAlignment(&tableHorizontalAlignment));*/

            auto tableHorizontalAlignment = adaptiveTable.HorizontalCellContentAlignment();

            // Save the current horizontal content alignment from the context, and replace it with the one
            // from the table if present
            /*ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> contextHorizontalAlignment;
            RETURN_IF_FAILED(renderContext->get_HorizontalContentAlignment(&contextHorizontalAlignment));
            if (tableHorizontalAlignment != nullptr)
            {
                RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(tableHorizontalAlignment.Get()));
            }*/
            auto contextHorizontalAlignment = renderContext.HorizontalContentAlignment();
            if (tableHorizontalAlignment != nullptr)
            {
                renderContext.HorizontalContentAlignment(tableHorizontalAlignment.Value());
            }

            // ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>>
            // tableVerticalAlignment;
            // RETURN_IF_FAILED(adaptiveTable->get_VerticalCellContentAlignment(&tableVerticalAlignment));

            // boolean showGridLines;
            // RETURN_IF_FAILED(adaptiveTable->get_ShowGridLines(&showGridLines));

            //// Create the column definitions
            // ComPtr<IVector<AdaptiveTableColumnDefinition*>> columns;
            // RETURN_IF_FAILED(adaptiveTable->get_Columns(&columns));

            // ComPtr<IVector<ColumnDefinition*>> xamlColumnDefinitions;
            // RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&xamlColumnDefinitions));
            auto tableVerticalAlignment = adaptiveTable.VerticalCellContentAlignment();
            bool showGridLines = adaptiveTable.ShowGridLines();

            auto columns = adaptiveTable.Columns();
            auto xamlColumnDefinitions = xamlGrid.ColumnDefinitions();

            /*  IterateOverVectorWithFailure<AdaptiveTableColumnDefinition, IAdaptiveTableColumnDefinition>(
                  columns.Get(),
                  true,
                  [&](IAdaptiveTableColumnDefinition* column)*/
            // TODO: how do we handle failure here? is there gonna be any????
            for (auto column : columns)
            {
                /*ComPtr<IColumnDefinition> xamlColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));

                RETURN_IF_FAILED(HandleTableColumnWidth(column, xamlColumnDefinition.Get()));

                RETURN_IF_FAILED(xamlColumnDefinitions->Append(xamlColumnDefinition.Get()));*/

                // return S_OK;
                rtxaml::Controls::ColumnDefinition xamlColumnDefinition{};
                HandleTableColumnWidth(column, xamlColumnDefinition);
                xamlColumnDefinitions.Append(xamlColumnDefinition);
            }

            // Create the rows
            /* ComPtr<IVector<AdaptiveTableRow*>> rows;
             RETURN_IF_FAILED(adaptiveTable->get_Rows(&rows));

             boolean firstRowAsHeaders;
             RETURN_IF_FAILED(adaptiveTable->get_FirstRowAsHeaders(&firstRowAsHeaders));

             ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle gridStyle;
             RETURN_IF_FAILED(adaptiveTable->get_GridStyle(&gridStyle));

             UINT rowNumber = 0;*/
            auto rows = adaptiveTable.Rows();

            bool firstRowAsHeaders = adaptiveTable.FirstRowAsHeaders();

            auto gridStyle = adaptiveTable.GridStyle();

            uint32_t rowNumber = 0;
            /* IterateOverVectorWithFailure<AdaptiveTableRow, IAdaptiveTableRow>(rows.Get(),
                                                                               true,
                                                                               [&](IAdaptiveTableRow* row)*/
            for (auto row : rows)
            {
                RenderRow(row, columns, renderContext, renderArgs, tableVerticalAlignment, firstRowAsHeaders, showGridLines, gridStyle, rowNumber, xamlGrid);

                rowNumber++;
            }

            // Reset the render context to its original horizontal content alignemnt value
            /* RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(contextHorizontalAlignment.Get()));

             ComPtr<IUIElement> xamlGridAsUIElement;
             RETURN_IF_FAILED(xamlGrid.As(&xamlGridAsUIElement));

             return xamlGridAsUIElement.CopyTo(tableControl);*/

            renderContext.HorizontalContentAlignment(contextHorizontalAlignment);
            return xamlGrid;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
