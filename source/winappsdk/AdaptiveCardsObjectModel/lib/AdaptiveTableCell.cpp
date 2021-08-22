// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableCell.h"

#include <windows.foundation.collections.h>
#include <windows.ui.xaml.h>
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    AdaptiveTableCell::AdaptiveTableCell() : m_bleedDirection(ABI::AdaptiveCards::ObjectModel::WinUI3::BleedDirection::None)
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveTableCell::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::TableCell> tableCell = std::make_shared<AdaptiveCards::TableCell>();
        return RuntimeClassInitialize(tableCell);
    }
    CATCH_RETURN();

    HRESULT AdaptiveTableCell::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TableCell>& sharedTableCell)
    try
    {
        if (sharedTableCell == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateContainedElementsProjection(sharedTableCell->GetItems(), m_items.Get());
        m_selectAction = GenerateActionProjection(sharedTableCell->GetSelectAction());
        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle>(sharedTableCell->GetStyle());
        if (sharedTableCell->GetVerticalContentAlignment().has_value())
        {
            m_verticalContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>(
                                     sharedTableCell->GetVerticalContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>>()
                    .get();
        }
        m_minHeight = sharedTableCell->GetMinHeight();
        m_bleed = sharedTableCell->GetBleed();
        m_bleedDirection = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::BleedDirection>(sharedTableCell->GetBleedDirection());

        const auto sharedRtl = sharedTableCell->GetRtl();
        if (sharedRtl)
        {
            m_rtl = winrt::box_value(sharedRtl.value()).as<ABI::Windows::Foundation::IReference<bool>>().get();
        }

        auto backgroundImage = sharedTableCell->GetBackgroundImage();
        if (backgroundImage != nullptr && !backgroundImage->GetUrl().empty())
        {
            m_backgroundImage =
                *winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedTableCell));
        return S_OK;
    }
    CATCH_RETURN();

    HRESULT AdaptiveTableCell::get_Items(_COM_Outptr_ IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    IFACEMETHODIMP AdaptiveTableCell::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        copy_to_abi(m_selectAction, action);
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveTableCell::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        winrt::copy_from_abi(m_selectAction, action);
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::TableCell;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::put_Style(ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_VerticalContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>** verticalContentAlignment)
    {
        return m_verticalContentAlignment.CopyTo(verticalContentAlignment);
    }

    HRESULT AdaptiveTableCell::put_VerticalContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>* verticalContentAlignment)
    {
        m_verticalContentAlignment = verticalContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** backgroundImage)
    {
        copy_to_abi(m_backgroundImage, backgroundImage);
        return S_OK;
    }

    HRESULT AdaptiveTableCell::put_BackgroundImage(_In_ IAdaptiveBackgroundImage* backgroundImage)
    {
        m_backgroundImage = copy_from_abi<decltype(m_backgroundImage)>(backgroundImage);
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_Rtl(_Out_ ABI::Windows::Foundation::IReference<bool>** rtl)
    {
        return m_rtl.CopyTo(rtl);
    }

    HRESULT AdaptiveTableCell::put_Rtl(ABI::Windows::Foundation::IReference<bool>* rtl)
    {
        m_rtl = rtl;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_MinHeight(_Out_ UINT32* minHeight)
    {
        *minHeight = m_minHeight;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::put_MinHeight(UINT32 minHeight)
    {
        m_minHeight = minHeight;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_Bleed(_Out_ boolean* isBleed)
    {
        *isBleed = m_bleed;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::put_Bleed(boolean isBleed)
    {
        m_bleed = isBleed;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_BleedDirection(ABI::AdaptiveCards::ObjectModel::WinUI3::BleedDirection* bleedDirection)
    {
        *bleedDirection = m_bleedDirection;
        return S_OK;
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveTableCell::GetSharedModel()
    {
        auto tableCell = std::make_shared<AdaptiveCards::TableCell>();
        THROW_IF_FAILED((CopySharedElementProperties(*tableCell)));

        if (m_selectAction)
        {
            tableCell->SetSelectAction(GenerateSharedAction(m_selectAction));
        }

        tableCell->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));

        if (m_verticalContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment verticalContentAlignmentValue;
            THROW_IF_FAILED(m_verticalContentAlignment->get_Value(&verticalContentAlignmentValue));
            tableCell->SetVerticalContentAlignment(
                static_cast<AdaptiveCards::VerticalContentAlignment>(verticalContentAlignmentValue));
        }

        tableCell->SetMinHeight(m_minHeight);

        auto adaptiveBackgroundImage = peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveBackgroundImage>(m_backgroundImage);
        std::shared_ptr<AdaptiveCards::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && (sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel()))
        {
            tableCell->SetBackgroundImage(std::move(sharedBackgroundImage));
        }

        tableCell->SetBleed(m_bleed);

        std::optional<bool> rtl;
        if (m_rtl)
        {
            boolean rtlValue;
            THROW_IF_FAILED(m_rtl->get_Value(&rtlValue));
            rtl = rtlValue;
        }
        tableCell->SetRtl(rtl);

        GenerateSharedElements(m_items.Get(), tableCell->GetItems());

        return tableCell;
    }
}
