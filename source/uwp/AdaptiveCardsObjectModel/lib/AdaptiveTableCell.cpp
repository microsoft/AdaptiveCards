// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTableCell.h"

#include "ObjectModelUtil.h"
#include "Vector.h"
#include <windows.foundation.collections.h>
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveTableCell::AdaptiveTableCell() : m_bleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveTableCell::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::TableCell> tableCell = std::make_shared<AdaptiveCards::TableCell>();
        return RuntimeClassInitialize(tableCell);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableCell::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TableCell>& sharedTableCell)
    try
    {
        if (sharedTableCell == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateContainedElementsProjection(sharedTableCell->GetItems(), m_items.Get());
        GenerateActionProjection(sharedTableCell->GetSelectAction(), &m_selectAction);
        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedTableCell->GetStyle());
        if (sharedTableCell->GetVerticalContentAlignment().has_value())
        {
            m_verticalContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
                                     sharedTableCell->GetVerticalContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>>()
                    .get();
        }
        m_minHeight = sharedTableCell->GetMinHeight();
        m_bleed = sharedTableCell->GetBleed();
        m_bleedDirection = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection>(sharedTableCell->GetBleedDirection());

        const auto sharedRtl = sharedTableCell->GetRtl();
        if (sharedRtl)
        {
            m_rtl = winrt::box_value(sharedRtl.value()).as<ABI::Windows::Foundation::IReference<bool>>().get();
        }

        auto backgroundImage = sharedTableCell->GetBackgroundImage();
        if (backgroundImage != nullptr && !backgroundImage->GetUrl().empty())
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveBackgroundImage>(m_backgroundImage.GetAddressOf(), backgroundImage));
        }

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedTableCell));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableCell::get_Items(_COM_Outptr_ IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    IFACEMETHODIMP AdaptiveTableCell::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    IFACEMETHODIMP AdaptiveTableCell::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::TableCell;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_VerticalContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalContentAlignment)
    {
        return m_verticalContentAlignment.CopyTo(verticalContentAlignment);
    }

    HRESULT AdaptiveTableCell::put_VerticalContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalContentAlignment)
    {
        m_verticalContentAlignment = verticalContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** backgroundImage)
    {
        return m_backgroundImage.CopyTo(backgroundImage);
    }

    HRESULT AdaptiveTableCell::put_BackgroundImage(_In_ IAdaptiveBackgroundImage* backgroundImage)
    {
        m_backgroundImage = backgroundImage;
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

    HRESULT AdaptiveTableCell::get_BleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection* bleedDirection)
    {
        *bleedDirection = m_bleedDirection;
        return S_OK;
    }

    HRESULT AdaptiveTableCell::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::TableCell> tableCell = std::make_shared<AdaptiveCards::TableCell>();
        RETURN_IF_FAILED(CopySharedElementProperties(*tableCell));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            tableCell->SetSelectAction(std::move(sharedAction));
        }

        tableCell->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));

        if (m_verticalContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalContentAlignmentValue;
            RETURN_IF_FAILED(m_verticalContentAlignment->get_Value(&verticalContentAlignmentValue));
            tableCell->SetVerticalContentAlignment(
                static_cast<AdaptiveCards::VerticalContentAlignment>(verticalContentAlignmentValue));
        }

        tableCell->SetMinHeight(m_minHeight);

        ComPtr<AdaptiveBackgroundImage> adaptiveBackgroundImage = PeekInnards<AdaptiveBackgroundImage>(m_backgroundImage);
        std::shared_ptr<AdaptiveCards::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && SUCCEEDED(adaptiveBackgroundImage->GetSharedModel(sharedBackgroundImage)))
        {
            tableCell->SetBackgroundImage(std::move(sharedBackgroundImage));
        }

        tableCell->SetBleed(m_bleed);

        std::optional<bool> rtl;
        if (m_rtl)
        {
            boolean rtlValue;
            RETURN_IF_FAILED(m_rtl->get_Value(&rtlValue));
            rtl = rtlValue;
        }
        tableCell->SetRtl(rtl);

        GenerateSharedElements(m_items.Get(), tableCell->GetItems());

        sharedModel = std::move(tableCell);
        return S_OK;
    }
    CATCH_RETURN;
}
