// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTableRenderer.h"
#include "util.h"
#include "XamlHelpers.h"

using namespace AdaptiveCards::Rendering::Uwp::XamlHelpers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveTableRenderer::RuntimeClassInitialize() noexcept
    try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableRenderer::RenderCell(
        _In_ IAdaptiveTableCell* cell,
        _In_ IAdaptiveRenderContext* renderContext,
        _In_ IAdaptiveRenderArgs* renderArgs,
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalContentAlignment,
        boolean showGridLines,
        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle,
        UINT32 rowNumber,
        UINT32 columnNumber,
        _COM_Outptr_ IFrameworkElement** renderedCell)
    {
        ComPtr<IAdaptiveTableCell> tableCell(cell);
        ComPtr<IAdaptiveContainer> tableCellAsContainer;
        RETURN_IF_FAILED(tableCell.As(&tableCellAsContainer));

        // Get the vertical content alignemnt from the cell
        ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>> cellVerticalAlignment;
        RETURN_IF_FAILED(tableCellAsContainer->get_VerticalContentAlignment(&cellVerticalAlignment));

        // If the cell doesn't have a vertical content alignment, pass in the one from the parent
        if (cellVerticalAlignment == nullptr)
        {
            RETURN_IF_FAILED(tableCellAsContainer->put_VerticalContentAlignment(verticalContentAlignment));
        }

        if (showGridLines)
        {
            // If we're showing grid lines add padding so the content isn't against the grid lines
            RETURN_IF_FAILED(renderArgs->put_AddContainerPadding(true));
        }

        // Render the cell as a container
        ComPtr<IAdaptiveElementRendererRegistration> rendererRegistration;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&rendererRegistration));

        ComPtr<IAdaptiveElementRenderer> containerRenderer;
        HString containerTypeString;
        RETURN_IF_FAILED(containerTypeString.Set(L"Container"));
        RETURN_IF_FAILED(rendererRegistration->Get(containerTypeString.Get(), &containerRenderer));

        ComPtr<IAdaptiveCardElement> tableCellAsCardElement;
        RETURN_IF_FAILED(tableCell.As(&tableCellAsCardElement));

        ComPtr<IUIElement> cellRenderedAsContainer;
        RETURN_IF_FAILED(containerRenderer->Render(tableCellAsCardElement.Get(), renderContext, renderArgs, &cellRenderedAsContainer));

        // Handle Grid Lines or Cell Spacing
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IFrameworkElement> cellFrameworkElement;
        if (showGridLines)
        {
            // If we're showing grid lines put the cell in a border
            ComPtr<IBorder> cellBorder =
                XamlHelpers::CreateABIClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

            ABI::Windows::UI::Color borderColor;
            RETURN_IF_FAILED(GetBorderColorFromStyle(gridStyle, hostConfig.Get(), &borderColor));
            RETURN_IF_FAILED(cellBorder->put_BorderBrush(XamlHelpers::GetSolidColorBrush(borderColor).Get()));

            // Create a border around the cell. Only set the top or left borders if we're in the top or leftmost
            // cells respectively in order to avoid double-thickness borders
            Thickness borderThickness = {0, 0, 1, 1};
            if (columnNumber == 0)
            {
                borderThickness.Left = 1;
            }
            if (rowNumber == 0)
            {
                borderThickness.Top = 1;
            }

            RETURN_IF_FAILED(cellBorder->put_BorderThickness(borderThickness));

            RETURN_IF_FAILED(cellBorder->put_Child(cellRenderedAsContainer.Get()));

            RETURN_IF_FAILED(cellBorder.As(&cellFrameworkElement));

            // Clear the container padding flag from the renderArgs
            RETURN_IF_FAILED(renderArgs->put_AddContainerPadding(false));
        }
        else
        {
            // If we're not showing gridlines, use the rendered cell as the frameworkElement, and add the cell spacing
            RETURN_IF_FAILED(cellRenderedAsContainer.As(&cellFrameworkElement));

            ComPtr<IAdaptiveTableConfig> tableConfig;
            RETURN_IF_FAILED(hostConfig->get_Table(&tableConfig));

            UINT32 cellSpacing;
            RETURN_IF_FAILED(tableConfig->get_CellSpacing(&cellSpacing));
            DOUBLE cellSpacingDouble = static_cast<DOUBLE>(cellSpacing);

            // Set left and top margin for each cell (to avoid double margins). Don't set the margin on topmost
            // or leftmost cells to avoid creating margin outside the table.
            Thickness marginThickness = {cellSpacingDouble, cellSpacingDouble, 0, 0};
            if (columnNumber == 0)
            {
                marginThickness.Left = 0;
            }
            if (rowNumber == 0)
            {
                marginThickness.Top = 0;
            }

            RETURN_IF_FAILED(cellFrameworkElement->put_Margin(marginThickness));
        }

        // If the cell didn't have a vertical content alignment when we started, set it back to null
        if (cellVerticalAlignment == nullptr)
        {
            RETURN_IF_FAILED(tableCellAsContainer->put_VerticalContentAlignment(nullptr));
        }

        RETURN_IF_FAILED(cellFrameworkElement.CopyTo(renderedCell));

        return S_OK;
    }

    HRESULT AdaptiveTableRenderer::RenderRow(
        _In_ IAdaptiveTableRow* row,
        _In_ IVector<AdaptiveTableColumnDefinition*>* columns,
        _In_ IAdaptiveRenderContext* renderContext,
        _In_ IAdaptiveRenderArgs* renderArgs,
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalContentAlignment,
        boolean firstRowAsHeaders,
        boolean showGridLines,
        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle,
        UINT32 rowNumber,
        _In_ IGrid* xamlGrid)
    {
        // Create the row definition and add it to the grid
        ComPtr<IRowDefinition> xamlRowDefinition =
            XamlHelpers::CreateABIClass<IRowDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));

        ComPtr<IVector<RowDefinition*>> xamlRowDefinitions;
        RETURN_IF_FAILED(xamlGrid->get_RowDefinitions(&xamlRowDefinitions));
        RETURN_IF_FAILED(xamlRowDefinitions->Append(xamlRowDefinition.Get()));

        // Save the current text style
        ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>> contextTextStyle;
        RETURN_IF_FAILED(renderContext->get_TextStyle(&contextTextStyle));

        // Set the column header style if this is the first row and firstRowAsHeaders is set
        if (rowNumber == 0 && firstRowAsHeaders)
        {
            // Set the text style to TextStyle::ColumnHeader
            RETURN_IF_FAILED(renderContext->put_TextStyle(
                winrt::box_value(winrt::AdaptiveCards::ObjectModel::Uwp::TextStyle::ColumnHeader)
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>>()
                    .get()));
        }

        // Save the current horizontal alignment from the context
        ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> contextHorizontalAlignment;
        RETURN_IF_FAILED(renderContext->get_HorizontalContentAlignment(&contextHorizontalAlignment));

        // Get the horizontal alignment for this row
        ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> rowHorizontalAlignment;
        RETURN_IF_FAILED(row->get_HorizontalCellContentAlignment(&rowHorizontalAlignment));

        // Get the vertical alignemnt for this row
        ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>> rowVerticalContentAlignment;
        RETURN_IF_FAILED(row->get_VerticalCellContentAlignment(&rowVerticalContentAlignment));

        // If there's no row vertical alignment, use the passed in value
        if (rowVerticalContentAlignment == nullptr)
        {
            rowVerticalContentAlignment = verticalContentAlignment;
        }

        ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        // Create the cells
        ComPtr<IVector<AdaptiveTableCell*>> cells;
        RETURN_IF_FAILED(row->get_Cells(&cells));

        UINT columnNumber = 0;
        IterateOverVectorWithFailure<AdaptiveTableCell, IAdaptiveTableCell>(cells.Get(), true, [&](IAdaptiveTableCell* cell) {
            // Get the horizontal alignment from the column definition
            ComPtr<IAdaptiveTableColumnDefinition> columnDefinition;
            RETURN_IF_FAILED(columns->GetAt(columnNumber, &columnDefinition));

            ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> columnHorizontalAlignment;
            RETURN_IF_FAILED(columnDefinition->get_HorizontalCellContentAlignment(&columnHorizontalAlignment));

            // Use row if present, then column, then table (which was passed in from the context)
            if (rowHorizontalAlignment != nullptr)
            {
                RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(rowHorizontalAlignment.Get()));
            }
            else if (columnHorizontalAlignment != nullptr)
            {
                RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(columnHorizontalAlignment.Get()));
            }
            else
            {
                RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(contextHorizontalAlignment.Get()));
            }

            // Render the cell
            ComPtr<IFrameworkElement> cellFrameworkElement;
            RETURN_IF_FAILED(
                RenderCell(cell, renderContext, renderArgs, rowVerticalContentAlignment.Get(), showGridLines, gridStyle, rowNumber, columnNumber, &cellFrameworkElement));

            // Set the row and column numbers on the cell
            RETURN_IF_FAILED(gridStatics->SetColumn(cellFrameworkElement.Get(), columnNumber));
            RETURN_IF_FAILED(gridStatics->SetRow(cellFrameworkElement.Get(), rowNumber));

            // Add the cell to the panel
            ComPtr<IGrid> localXamlGrid(xamlGrid);
            ComPtr<IPanel> xamlGridAsPanel;
            RETURN_IF_FAILED(localXamlGrid.As(&xamlGridAsPanel));
            XamlHelpers::AppendXamlElementToPanel(cellFrameworkElement.Get(), xamlGridAsPanel.Get());

            columnNumber++;
            return S_OK;
        });

        // Reset the render context to its original values
        RETURN_IF_FAILED(renderContext->put_TextStyle(contextTextStyle.Get()));
        RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(contextHorizontalAlignment.Get()));

        return S_OK;
    }

    HRESULT AdaptiveTableRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                          _In_ IAdaptiveRenderContext* renderContext,
                                          _In_ IAdaptiveRenderArgs* renderArgs,
                                          _COM_Outptr_ IUIElement** tableControl) noexcept
    try
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTable> adaptiveTable;
        RETURN_IF_FAILED(cardElement.As(&adaptiveTable));

        // Create a grid to represent the table
        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));

        // Get the vertical content alignment from the table
        ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> tableHorizontalAlignment;
        RETURN_IF_FAILED(adaptiveTable->get_HorizontalCellContentAlignment(&tableHorizontalAlignment));

        // Save the current horizontal content alignment from the context, and replace it with the one
        // from the table if present
        ComPtr<ABI::Windows::Foundation::IReference<HAlignment>> contextHorizontalAlignment;
        RETURN_IF_FAILED(renderContext->get_HorizontalContentAlignment(&contextHorizontalAlignment));
        if (tableHorizontalAlignment != nullptr)
        {
            RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(tableHorizontalAlignment.Get()));
        }

        ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>> tableVerticalAlignment;
        RETURN_IF_FAILED(adaptiveTable->get_VerticalCellContentAlignment(&tableVerticalAlignment));

        boolean showGridLines;
        RETURN_IF_FAILED(adaptiveTable->get_ShowGridLines(&showGridLines));

        // Create the column definitions
        ComPtr<IVector<AdaptiveTableColumnDefinition*>> columns;
        RETURN_IF_FAILED(adaptiveTable->get_Columns(&columns));

        ComPtr<IVector<ColumnDefinition*>> xamlColumnDefinitions;
        RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&xamlColumnDefinitions));

        IterateOverVectorWithFailure<AdaptiveTableColumnDefinition, IAdaptiveTableColumnDefinition>(
            columns.Get(), true, [&](IAdaptiveTableColumnDefinition* column) {
                ComPtr<IColumnDefinition> xamlColumnDefinition = XamlHelpers::CreateABIClass<IColumnDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));

                RETURN_IF_FAILED(HandleTableColumnWidth(column, xamlColumnDefinition.Get()));

                RETURN_IF_FAILED(xamlColumnDefinitions->Append(xamlColumnDefinition.Get()));

                return S_OK;
            });

        // Create the rows
        ComPtr<IVector<AdaptiveTableRow*>> rows;
        RETURN_IF_FAILED(adaptiveTable->get_Rows(&rows));

        boolean firstRowAsHeaders;
        RETURN_IF_FAILED(adaptiveTable->get_FirstRowAsHeaders(&firstRowAsHeaders));

        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle;
        RETURN_IF_FAILED(adaptiveTable->get_GridStyle(&gridStyle));

        UINT rowNumber = 0;
        IterateOverVectorWithFailure<AdaptiveTableRow, IAdaptiveTableRow>(rows.Get(), true, [&](IAdaptiveTableRow* row) {
            RETURN_IF_FAILED(RenderRow(row,
                                       columns.Get(),
                                       renderContext,
                                       renderArgs,
                                       tableVerticalAlignment.Get(),
                                       firstRowAsHeaders,
                                       showGridLines,
                                       gridStyle,
                                       rowNumber,
                                       xamlGrid.Get()));

            rowNumber++;
            return S_OK;
        });

        // Reset the render context to its original horizontal content alignemnt value
        RETURN_IF_FAILED(renderContext->put_HorizontalContentAlignment(contextHorizontalAlignment.Get()));

        ComPtr<IUIElement> xamlGridAsUIElement;
        RETURN_IF_FAILED(xamlGrid.As(&xamlGridAsUIElement));

        return xamlGridAsUIElement.CopyTo(tableControl);
    }
    CATCH_RETURN;
}
