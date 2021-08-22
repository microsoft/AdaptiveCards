// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainer.h"

#include "ObjectModelUtil.h"
#include "Vector.h"
#include <windows.foundation.collections.h>
#include <winrt/Windows.Foundation.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    AdaptiveContainer::AdaptiveContainer() :
        m_bleedDirection(ABI::AdaptiveCards::ObjectModel::WinUI3::BleedDirection::None)
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveContainer::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::Container> container = std::make_shared<AdaptiveCards::Container>();
        return RuntimeClassInitialize(container);
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainer::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Container>& sharedContainer)
    try
    {
        if (sharedContainer == nullptr)
        {
            return E_INVALIDARG;
        }

        if (sharedContainer->GetVerticalContentAlignment().has_value())
        {
            m_verticalContentAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>(
                                     sharedContainer->GetVerticalContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>>()
                    .get();
        }

        GenerateContainedElementsProjection(sharedContainer->GetItems(), m_items.Get());
        m_selectAction = GenerateActionProjection(sharedContainer->GetSelectAction());
        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle>(sharedContainer->GetStyle());
        m_minHeight = sharedContainer->GetMinHeight();
        m_bleed = sharedContainer->GetBleed();
        m_bleedDirection =
            static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::BleedDirection>(sharedContainer->GetBleedDirection());

        const auto sharedRtl = sharedContainer->GetRtl();
        if (sharedRtl)
        {
            m_rtl = winrt::box_value(sharedRtl.value()).as<ABI::Windows::Foundation::IReference<bool>>().get();
        }

        auto backgroundImage = sharedContainer->GetBackgroundImage();
        if (backgroundImage != nullptr && !backgroundImage->GetUrl().empty())
        {
            m_backgroundImage =
                *winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedContainer));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainer::get_Items(_COM_Outptr_ IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    IFACEMETHODIMP AdaptiveContainer::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        copy_to_abi(m_selectAction, action);
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveContainer::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        winrt::copy_from_abi(m_selectAction, action);
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Container;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_Style(ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_VerticalContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>** verticalContentAlignment)
    {
        return m_verticalContentAlignment.CopyTo(verticalContentAlignment);
    }

    HRESULT AdaptiveContainer::put_VerticalContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment>* verticalContentAlignment)
    {
        m_verticalContentAlignment = verticalContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** backgroundImage)
    {
        copy_to_abi(m_backgroundImage, backgroundImage);
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_BackgroundImage(_In_ IAdaptiveBackgroundImage* backgroundImage)
    {
        m_backgroundImage = copy_from_abi<decltype(m_backgroundImage)>(backgroundImage);
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_Rtl(_Out_ ABI::Windows::Foundation::IReference<bool>** rtl)
    {
        return m_rtl.CopyTo(rtl);
    }

    HRESULT AdaptiveContainer::put_Rtl(ABI::Windows::Foundation::IReference<bool>* rtl)
    {
        m_rtl = rtl;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_MinHeight(_Out_ UINT32* minHeight)
    {
        *minHeight = m_minHeight;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_MinHeight(UINT32 minHeight)
    {
        m_minHeight = minHeight;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_Bleed(_Out_ boolean* isBleed)
    {
        *isBleed = m_bleed;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_Bleed(boolean isBleed)
    {
        m_bleed = isBleed;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_BleedDirection(ABI::AdaptiveCards::ObjectModel::WinUI3::BleedDirection* bleedDirection)
    {
        // TODO: Current behavior is broken because it doesn't update when bleed updates. Unfortunately, neither does
        // the shared model logic.
        *bleedDirection = m_bleedDirection;
        return S_OK;
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveContainer::GetSharedModel()
    {
        auto container = std::make_shared<AdaptiveCards::Container>();
        THROW_IF_FAILED(CopySharedElementProperties(*container));

        if (m_selectAction != nullptr)
        {
            container->SetSelectAction(GenerateSharedAction(m_selectAction));
        }

        if (m_verticalContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment verticalContentAlignmentValue;
            THROW_IF_FAILED(m_verticalContentAlignment->get_Value(&verticalContentAlignmentValue));
            container->SetVerticalContentAlignment(static_cast<AdaptiveCards::VerticalContentAlignment>(verticalContentAlignmentValue));
        }

        container->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));
        container->SetMinHeight(m_minHeight);

        if (auto adaptiveBackgroundImage =
                peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveBackgroundImage>(m_backgroundImage))
        {
            if (auto sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel())
            {
                container->SetBackgroundImage(std::move(sharedBackgroundImage));
            }
        }

        container->SetBleed(m_bleed);

        std::optional<bool> rtl;
        if (m_rtl)
        {
            boolean rtlValue;
            THROW_IF_FAILED(m_rtl->get_Value(&rtlValue));
            rtl = rtlValue;
        }
        container->SetRtl(rtl);

        GenerateSharedElements(m_items.Get(), container->GetItems());

        return container;
    }
}
