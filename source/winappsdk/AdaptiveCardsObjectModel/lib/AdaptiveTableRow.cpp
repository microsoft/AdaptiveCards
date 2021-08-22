// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableRow.h"
#include "AdaptiveTableCell.h"
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    AdaptiveTableRow::AdaptiveTableRow()
    {
        m_cells = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableCell*>>();
    }

    HRESULT AdaptiveTableRow::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::TableRow> tableRow = std::make_shared<AdaptiveCards::TableRow>();
        return RuntimeClassInitialize(tableRow);
    }
    CATCH_RETURN();

    HRESULT AdaptiveTableRow::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TableRow>& sharedTableRow)
    try
    {
        if (sharedTableRow->GetVerticalCellContentAlignment().has_value())
        {
            m_verticalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>(
                                     sharedTableRow->GetVerticalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>>()
                    .get();
        }

        if (sharedTableRow->GetHorizontalCellContentAlignment().has_value())
        {
            m_horizontalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::HAlignment>(
                                     sharedTableRow->GetHorizontalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment>>()
                    .get();
        }

        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle>(sharedTableRow->GetStyle());

        GenerateTableCellsProjection(sharedTableRow->GetCells(), m_cells.Get());

        return S_OK;
    }
    CATCH_RETURN();

    HRESULT AdaptiveTableRow::get_ElementType(ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType* elementType)
    {
        *elementType = ElementType::TableRow;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::get_Cells(
        ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTableCell*>** cells)
    {
        return m_cells.CopyTo(cells);
    }

    HRESULT AdaptiveTableRow::get_VerticalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>** verticalCellContentAlignment)
    {
        return m_verticalCellContentAlignment.CopyTo(verticalCellContentAlignment);
    }

    HRESULT AdaptiveTableRow::put_VerticalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>* verticalCellContentAlignment)
    {
        m_verticalCellContentAlignment = verticalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::get_HorizontalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment>** horizontalCellContentAlignment)
    {
        return m_horizontalCellContentAlignment.CopyTo(horizontalCellContentAlignment);
    }

    HRESULT AdaptiveTableRow::put_HorizontalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment>* horizontalCellContentAlignment)
    {
        m_horizontalCellContentAlignment = horizontalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::put_Style(ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTableRow::GetSharedModel()
    {
        auto tableRow = std::make_shared<AdaptiveCards::TableRow>();

        if (m_verticalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment verticalCellContentAlignmentValue;
            THROW_IF_FAILED(m_verticalCellContentAlignment->get_Value(&verticalCellContentAlignmentValue));
            tableRow->SetVerticalCellContentAlignment(
                static_cast<AdaptiveCards::VerticalContentAlignment>(verticalCellContentAlignmentValue));
        }

        if (m_horizontalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment horizontalCellContentAlignmentValue;
            THROW_IF_FAILED(m_horizontalCellContentAlignment->get_Value(&horizontalCellContentAlignmentValue));
            tableRow->SetHorizontalCellContentAlignment(
                static_cast<AdaptiveCards::HorizontalAlignment>(horizontalCellContentAlignmentValue));
        }

        tableRow->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));

        GenerateSharedTableCells(m_cells.Get(), tableRow->GetCells());

        return tableRow;
    }
}
