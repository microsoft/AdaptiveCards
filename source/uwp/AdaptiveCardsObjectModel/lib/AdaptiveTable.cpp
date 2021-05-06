// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTable.h"
#include "AdaptiveTableRow.h"
#include "AdaptiveTableColumnDefinition.h"
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveTable::AdaptiveTable()
    {
        m_rows = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableRow*>>();
        m_columnDefinitions =
            Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableColumnDefinition*>>();
    }

    HRESULT AdaptiveTable::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::Table> table = std::make_shared<AdaptiveCards::Table>();
        return RuntimeClassInitialize(table);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTable::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Table>& sharedTable)
    try
    {
        m_showGridLines = sharedTable->GetShowGridLines();
        m_firstRowAsHeaders = sharedTable->GetFirstRowAsHeaders();

        if (sharedTable->GetVerticalCellContentAlignment().has_value())
        {
            m_verticalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
                                     sharedTable->GetVerticalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>>()
                    .get();
        }

        if (sharedTable->GetHorizontalCellContentAlignment().has_value())
        {
            m_horizontalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HAlignment>(
                                     sharedTable->GetHorizontalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>>()
                    .get();
        }

        m_gridStyle = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedTable->GetGridStyle());

        GenerateTableRowsProjection(sharedTable->GetRows(), m_rows.Get());
        GenerateTableColumnDefinitionsProjection(sharedTable->GetColumns(), m_columnDefinitions.Get());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedTable));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTable::get_ElementType(ABI::AdaptiveCards::ObjectModel::Uwp::ElementType* elementType)
    {
        *elementType = ElementType::Table;
        return S_OK;
    }

    HRESULT AdaptiveTable::get_Rows(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableRow*>** rows)
    {
        return m_rows.CopyTo(rows);
    }

    HRESULT AdaptiveTable::get_Columns(
        ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableColumnDefinition*>** columns)
    {
        return m_columnDefinitions.CopyTo(columns);
    }

    HRESULT AdaptiveTable::get_ShowGridLines(boolean* showGridLines)
    {
        *showGridLines = m_showGridLines;
        return S_OK;
    }

    HRESULT AdaptiveTable::put_ShowGridLines(boolean showGridLines)
    {
        m_showGridLines = showGridLines;
        return S_OK;
    }

    HRESULT AdaptiveTable::get_FirstRowAsHeaders(boolean* firstRowAsHeaders)
    {
        *firstRowAsHeaders = m_firstRowAsHeaders;
        return S_OK;
    }

    HRESULT AdaptiveTable::put_FirstRowAsHeaders(boolean firstRowAsHeaders)
    {
        m_firstRowAsHeaders = firstRowAsHeaders;
        return S_OK;
    }

    HRESULT AdaptiveTable::get_VerticalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalCellContentAlignment)
    {
        return m_verticalCellContentAlignment.CopyTo(verticalCellContentAlignment);
    }

    HRESULT AdaptiveTable::put_VerticalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalCellContentAlignment)
    {
        m_verticalCellContentAlignment = verticalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTable::get_HorizontalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalCellContentAlignment)
    {
        return m_horizontalCellContentAlignment.CopyTo(horizontalCellContentAlignment);
    }

    HRESULT AdaptiveTable::put_HorizontalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalCellContentAlignment)
    {
        m_horizontalCellContentAlignment = horizontalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTable::get_GridStyle(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* gridStyle)
    {
        *gridStyle = m_gridStyle;
        return S_OK;
    }

    HRESULT AdaptiveTable::put_GridStyle(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle gridStyle)
    {
        m_gridStyle = gridStyle;
        return S_OK;
    }

    HRESULT AdaptiveTable::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::Table> table = std::make_shared<AdaptiveCards::Table>();

        RETURN_IF_FAILED(CopySharedElementProperties(*table));

        table->SetShowGridLines(m_showGridLines);
        table->SetFirstRowAsHeaders(m_firstRowAsHeaders);

        if (m_verticalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalCellContentAlignmentValue;
            RETURN_IF_FAILED(m_verticalCellContentAlignment->get_Value(&verticalCellContentAlignmentValue));
            table->SetVerticalCellContentAlignment(static_cast<AdaptiveCards::VerticalContentAlignment>(verticalCellContentAlignmentValue));
        }

        if (m_horizontalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment horizontalCellContentAlignmentValue;
            RETURN_IF_FAILED(m_horizontalCellContentAlignment->get_Value(&horizontalCellContentAlignmentValue));
            table->SetHorizontalCellContentAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(horizontalCellContentAlignmentValue));
        }

        table->SetGridStyle(static_cast<AdaptiveCards::ContainerStyle>(m_gridStyle));

        GenerateSharedTableRows(m_rows.Get(), table->GetRows());
        GenerateSharedTableColumnDefinitions(m_columnDefinitions.Get(), table->GetColumns());

        sharedModel = std::move(table);
        return S_OK;
    }
    CATCH_RETURN;
}
