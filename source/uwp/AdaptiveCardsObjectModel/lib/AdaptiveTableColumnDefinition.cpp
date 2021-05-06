// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableColumnDefinition.h"
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveTableColumnDefinition::AdaptiveTableColumnDefinition() {}

    HRESULT AdaptiveTableColumnDefinition::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::TableColumnDefinition> tableColumnDefinition =
            std::make_shared<AdaptiveCards::TableColumnDefinition>();
        return RuntimeClassInitialize(tableColumnDefinition);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableColumnDefinition::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TableColumnDefinition>& sharedTableColumnDefinition)
    try
    {
        if (sharedTableColumnDefinition->GetVerticalCellContentAlignment().has_value())
        {
            m_verticalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
                                     sharedTableColumnDefinition->GetVerticalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>>()
                    .get();
        }

        if (sharedTableColumnDefinition->GetHorizontalCellContentAlignment().has_value())
        {
            m_horizontalCellContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HAlignment>(
                                     sharedTableColumnDefinition->GetHorizontalCellContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>>()
                    .get();
        }

        const auto sharedWidth = sharedTableColumnDefinition->GetWidth();
        if (sharedWidth)
        {
            m_width = winrt::box_value(sharedWidth.value()).as<ABI::Windows::Foundation::IReference<UINT32>>().get();
        }

        const auto sharedPixelWidth = sharedTableColumnDefinition->GetPixelWidth();
        if (sharedPixelWidth)
        {
            m_pixelWidth = winrt::box_value(sharedPixelWidth.value()).as<ABI::Windows::Foundation::IReference<UINT32>>().get();
        }

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableColumnDefinition::get_VerticalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalCellContentAlignment)
    {
        return m_verticalCellContentAlignment.CopyTo(verticalCellContentAlignment);
    }

    HRESULT AdaptiveTableColumnDefinition::put_VerticalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalCellContentAlignment)
    {
        m_verticalCellContentAlignment = verticalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::get_HorizontalCellContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalCellContentAlignment)
    {
        return m_horizontalCellContentAlignment.CopyTo(horizontalCellContentAlignment);
    }

    HRESULT AdaptiveTableColumnDefinition::put_HorizontalCellContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalCellContentAlignment)
    {
        m_horizontalCellContentAlignment = horizontalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::get_Width(ABI::Windows::Foundation::IReference<UINT32>** width)
    {
        m_width.CopyTo(width);
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::put_Width(ABI::Windows::Foundation::IReference<UINT32>* width)
    {
        m_width = width;
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::get_PixelWidth(ABI::Windows::Foundation::IReference<UINT32>** pixelWidth)
    {
        m_pixelWidth.CopyTo(pixelWidth);
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::put_PixelWidth(ABI::Windows::Foundation::IReference<UINT32>* pixelWidth)
    {
        m_pixelWidth = pixelWidth;
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::GetSharedModel(std::shared_ptr<AdaptiveCards::TableColumnDefinition>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::TableColumnDefinition> tableColumnDefinition =
            std::make_shared<AdaptiveCards::TableColumnDefinition>();

        if (m_verticalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalCellContentAlignmentValue;
            RETURN_IF_FAILED(m_verticalCellContentAlignment->get_Value(&verticalCellContentAlignmentValue));
            tableColumnDefinition->SetVerticalCellContentAlignment(
                static_cast<AdaptiveCards::VerticalContentAlignment>(verticalCellContentAlignmentValue));
        }

        if (m_horizontalCellContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment horizontalCellContentAlignmentValue;
            RETURN_IF_FAILED(m_horizontalCellContentAlignment->get_Value(&horizontalCellContentAlignmentValue));
            tableColumnDefinition->SetHorizontalCellContentAlignment(
                static_cast<AdaptiveCards::HorizontalAlignment>(horizontalCellContentAlignmentValue));
        }

        std::optional<UINT32> width;
        if (m_width)
        {
            UINT32 widthValue;
            RETURN_IF_FAILED(m_width->get_Value(&widthValue));
            width = widthValue;
        }
        tableColumnDefinition->SetWidth(width);

        std::optional<UINT32> pixelWidth;
        if (m_pixelWidth)
        {
            UINT32 pixelWidthValue;
            RETURN_IF_FAILED(m_pixelWidth->get_Value(&pixelWidthValue));
            pixelWidth = pixelWidthValue;
        }
        tableColumnDefinition->SetPixelWidth(pixelWidth);

        sharedModel = std::move(tableColumnDefinition);
        return S_OK;
    }
    CATCH_RETURN;
}
