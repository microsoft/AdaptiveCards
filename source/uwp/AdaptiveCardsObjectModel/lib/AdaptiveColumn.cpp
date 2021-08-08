// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveColumn.h"

#include "ObjectModelUtil.h"
#include "Vector.h"
#include <windows.foundation.collections.h>
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveColumn::AdaptiveColumn() : m_bleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveColumn::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::Column> column = std::make_shared<AdaptiveCards::Column>();
        return RuntimeClassInitialize(column);
    }
    CATCH_RETURN;

    HRESULT AdaptiveColumn::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Column>& sharedColumn)
    try
    {
        GenerateContainedElementsProjection(sharedColumn->GetItems(), m_items.Get());
        GenerateActionProjection(sharedColumn->GetSelectAction(), &m_selectAction);

        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedColumn->GetStyle());

        if (sharedColumn->GetVerticalContentAlignment().has_value())
        {
            m_verticalContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
                                     sharedColumn->GetVerticalContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>>()
                    .get();
        }

        m_bleed = sharedColumn->GetBleed();
        m_bleedDirection = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection>(sharedColumn->GetBleedDirection());

        RETURN_IF_FAILED(UTF8ToHString(sharedColumn->GetWidth(), m_width.GetAddressOf()));
        m_pixelWidth = sharedColumn->GetPixelWidth();
        m_minHeight = sharedColumn->GetMinHeight();

        auto backgroundImage = sharedColumn->GetBackgroundImage();
        if (backgroundImage != nullptr && !backgroundImage->GetUrl().empty())
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveBackgroundImage>(m_backgroundImage.GetAddressOf(), backgroundImage));
        }

        const auto sharedRtl = sharedColumn->GetRtl();
        if (sharedRtl)
        {
            m_rtl = winrt::box_value(sharedRtl.value()).as<ABI::Windows::Foundation::IReference<bool>>().get();
        }

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedColumn));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveColumn::get_Width(_Outptr_ HSTRING* width) { return m_width.CopyTo(width); }

    HRESULT AdaptiveColumn::put_Width(_In_ HSTRING width)
    {
        RETURN_IF_FAILED(m_width.Set(width));

        RETURN_IF_FAILED(put_PixelWidth(ParseSizeForPixelSize(HStringToUTF8(width), nullptr).value_or(0)));
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_PixelWidth(_Out_ UINT32* pixelWidth) { return *pixelWidth = m_pixelWidth; }

    HRESULT AdaptiveColumn::put_PixelWidth(UINT32 pixelWidth) { return m_pixelWidth = pixelWidth; }

    HRESULT AdaptiveColumn::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveColumn::put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_VerticalContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalAlignment)
    {
        return m_verticalContentAlignment.CopyTo(verticalAlignment);
    }

    HRESULT AdaptiveColumn::put_VerticalContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalAlignment)
    {
        m_verticalContentAlignment = verticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** backgroundImage)
    {
        return m_backgroundImage.CopyTo(backgroundImage);
    }

    HRESULT AdaptiveColumn::put_BackgroundImage(_In_ IAdaptiveBackgroundImage* backgroundImage)
    {
        m_backgroundImage = backgroundImage;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_Rtl(_Out_ ABI::Windows::Foundation::IReference<bool>** rtl)
    {
        return m_rtl.CopyTo(rtl);
    }

    HRESULT AdaptiveColumn::put_Rtl(ABI::Windows::Foundation::IReference<bool>* rtl)
    {
        m_rtl = rtl;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_MinHeight(_Out_ UINT32* minHeight)
    {
        *minHeight = m_minHeight;
        return S_OK;
    }

    HRESULT AdaptiveColumn::put_MinHeight(UINT32 minHeight)
    {
        m_minHeight = minHeight;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_Items(_COM_Outptr_ IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    HRESULT AdaptiveColumn::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    HRESULT AdaptiveColumn::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_Bleed(_Out_ boolean* isBleed)
    {
        *isBleed = m_bleed;
        return S_OK;
    }

    HRESULT AdaptiveColumn::put_Bleed(boolean isBleed)
    {
        m_bleed = isBleed;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_BleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection* bleedDirection)
    {
        // TODO: Current behavior is broken because it doesn't update when bleed updates. Unfortunately, neither does
        // the shared model logic.
        *bleedDirection = m_bleedDirection;
        return S_OK;
    }

    HRESULT AdaptiveColumn::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Column;
        return S_OK;
    }

    HRESULT AdaptiveColumn::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::Column> column = std::make_shared<AdaptiveCards::Column>();
        RETURN_IF_FAILED(CopySharedElementProperties(*column));

        column->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));

        if (m_verticalContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalContentAlignmentValue;
            RETURN_IF_FAILED(m_verticalContentAlignment->get_Value(&verticalContentAlignmentValue));
            column->SetVerticalContentAlignment(static_cast<AdaptiveCards::VerticalContentAlignment>(verticalContentAlignmentValue));
        }

        if (m_pixelWidth)
        {
            column->SetPixelWidth(m_pixelWidth);
        }
        else
        {
            column->SetWidth(HStringToUTF8(m_width.Get()));
        }

        column->SetMinHeight(m_minHeight);
        column->SetBleed(m_bleed);

        ComPtr<AdaptiveBackgroundImage> adaptiveBackgroundImage = PeekInnards<AdaptiveBackgroundImage>(m_backgroundImage);
        std::shared_ptr<AdaptiveCards::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && SUCCEEDED(adaptiveBackgroundImage->GetSharedModel(sharedBackgroundImage)))
        {
            column->SetBackgroundImage(std::move(sharedBackgroundImage));
        }

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            column->SetSelectAction(std::move(sharedAction));
        }

        std::optional<bool> rtl;
        if (m_rtl)
        {
            boolean rtlValue;
            RETURN_IF_FAILED(m_rtl->get_Value(&rtlValue));
            rtl = rtlValue;
        }
        column->SetRtl(rtl);

        GenerateSharedElements(m_items.Get(), column->GetItems());

        sharedModel = std::move(column);
        return S_OK;
    }
    CATCH_RETURN;
}
