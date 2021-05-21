// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableColumnDefinition.h"
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
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
        m_verticalCellContentAlignment = static_cast<ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment>(
            sharedTableColumnDefinition->GetVerticalCellContentAlignment());

        m_horizontalCellContentAlignment = static_cast<ABI::AdaptiveCards::Rendering::Uwp::HAlignment>(
            sharedTableColumnDefinition->GetHorizontalCellContentAlignment());

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

    HRESULT AdaptiveTableColumnDefinition::get_VerticalCellContentAlignment(ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment* verticalCellContentAlignment)
    {
        *verticalCellContentAlignment = m_verticalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::put_VerticalCellContentAlignment(ABI::AdaptiveCards::Rendering::Uwp::VerticalContentAlignment verticalCellContentAlignment)
    {
        m_verticalCellContentAlignment = verticalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::get_HorizontalCellContentAlignment(ABI::AdaptiveCards::Rendering::Uwp::HAlignment* horizontalCellContentAlignment)
    {
        *horizontalCellContentAlignment = m_horizontalCellContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableColumnDefinition::put_HorizontalCellContentAlignment(ABI::AdaptiveCards::Rendering::Uwp::HAlignment horizontalCellContentAlignment)
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

        tableColumnDefinition->SetVerticalCellContentAlignment(
            static_cast<AdaptiveCards::VerticalAlignment>(m_verticalCellContentAlignment));

        tableColumnDefinition->SetHorizontalCellContentAlignment(
            static_cast<AdaptiveCards::HorizontalAlignment>(m_horizontalCellContentAlignment));

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
