// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableRow.h"
#include "AdaptiveTableCell.h"
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveTableRow::AdaptiveTableRow()
    {
        m_cells = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableCell*>>();
    }

    HRESULT AdaptiveTableRow::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::TableRow> tableRow = std::make_shared<AdaptiveCards::TableRow>();
        return RuntimeClassInitialize(tableRow);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableRow::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TableRow>& sharedTableRow)
    try
    {
        if (sharedTableRow->GetVerticalCellContentAlignment().has_value())
        {
            m_verticalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
                                     sharedTableRow->GetVerticalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>>()
                    .get();
        }

        if (sharedTableRow->GetHorizontalCellContentAlignment().has_value())
        {
            m_horizontalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HAlignment>(
                                     sharedTableRow->GetHorizontalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>>()
                    .get();
        }

        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedTableRow->GetStyle());

        GenerateTableCellsProjection(sharedTableRow->GetCells(), m_cells.Get());

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableRow::get_ElementType(ABI::AdaptiveCards::ObjectModel::Uwp::ElementType* elementType)
    {
        *elementType = ElementType::TableRow;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::get_Cells(
        ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableCell*>** cells)
    {
        return m_cells.CopyTo(cells);
    }

    HRESULT AdaptiveTableRow::get_VerticalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalCellContentAlignment)
    {
        return m_verticalCellContentAlignment.CopyTo(verticalCellContentAlignment);
    }

    HRESULT AdaptiveTableRow::put_VerticalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalCellContentAlignment)
    {
        m_verticalCellContentAlignment = verticalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::get_HorizontalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalCellContentAlignment)
    {
        return m_horizontalCellContentAlignment.CopyTo(horizontalCellContentAlignment);
    }

    HRESULT AdaptiveTableRow::put_HorizontalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalCellContentAlignment)
    {
        m_horizontalCellContentAlignment = horizontalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveTableRow::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::TableRow> tableRow = std::make_shared<AdaptiveCards::TableRow>();

        if (m_verticalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalCellContentAlignmentValue;
            RETURN_IF_FAILED(m_verticalCellContentAlignment->get_Value(&verticalCellContentAlignmentValue));
            tableRow->SetVerticalCellContentAlignment(
                static_cast<AdaptiveCards::VerticalContentAlignment>(verticalCellContentAlignmentValue));
        }

        if (m_horizontalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment horizontalCellContentAlignmentValue;
            RETURN_IF_FAILED(m_horizontalCellContentAlignment->get_Value(&horizontalCellContentAlignmentValue));
            tableRow->SetHorizontalCellContentAlignment(
                static_cast<AdaptiveCards::HorizontalAlignment>(horizontalCellContentAlignmentValue));
        }

        tableRow->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));

        GenerateSharedTableCells(m_cells.Get(), tableRow->GetCells());

        sharedModel = std::move(tableRow);
        return S_OK;
    }
    CATCH_RETURN;
}
