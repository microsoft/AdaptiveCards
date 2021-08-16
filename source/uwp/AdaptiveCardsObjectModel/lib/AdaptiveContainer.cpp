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
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveContainer::AdaptiveContainer() :
        m_bleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
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
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
                                     sharedContainer->GetVerticalContentAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>>()
                    .get();
        }

        GenerateContainedElementsProjection(sharedContainer->GetItems(), m_items.Get());
        GenerateActionProjection(sharedContainer->GetSelectAction(), &m_selectAction);
        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedContainer->GetStyle());
        m_minHeight = sharedContainer->GetMinHeight();
        m_bleed = sharedContainer->GetBleed();
        m_bleedDirection =
            static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection>(sharedContainer->GetBleedDirection());

        const auto sharedRtl = sharedContainer->GetRtl();
        if (sharedRtl)
        {
            m_rtl = winrt::box_value(sharedRtl.value()).as<ABI::Windows::Foundation::IReference<bool>>().get();
        }

        auto backgroundImage = sharedContainer->GetBackgroundImage();
        if (backgroundImage != nullptr && !backgroundImage->GetUrl().empty())
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveBackgroundImage>(m_backgroundImage.GetAddressOf(), backgroundImage));
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
        return m_selectAction.CopyTo(action);
    }

    IFACEMETHODIMP AdaptiveContainer::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Container;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_VerticalContentAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalContentAlignment)
    {
        return m_verticalContentAlignment.CopyTo(verticalContentAlignment);
    }

    HRESULT AdaptiveContainer::put_VerticalContentAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalContentAlignment)
    {
        m_verticalContentAlignment = verticalContentAlignment;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_BackgroundImage(_Outptr_ IAdaptiveBackgroundImage** backgroundImage)
    {
        return m_backgroundImage.CopyTo(backgroundImage);
    }

    HRESULT AdaptiveContainer::put_BackgroundImage(_In_ IAdaptiveBackgroundImage* backgroundImage)
    {
        m_backgroundImage = backgroundImage;
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

    HRESULT AdaptiveContainer::get_BleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection* bleedDirection)
    {
        // TODO: Current behavior is broken because it doesn't update when bleed updates. Unfortunately, neither does
        // the shared model logic.
        *bleedDirection = m_bleedDirection;
        return S_OK;
    }

    HRESULT AdaptiveContainer::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::Container> container = std::make_shared<AdaptiveCards::Container>();
        RETURN_IF_FAILED(CopySharedElementProperties(*container));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            container->SetSelectAction(std::move(sharedAction));
        }

        if (m_verticalContentAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment verticalContentAlignmentValue;
            RETURN_IF_FAILED(m_verticalContentAlignment->get_Value(&verticalContentAlignmentValue));
            container->SetVerticalContentAlignment(static_cast<AdaptiveCards::VerticalContentAlignment>(verticalContentAlignmentValue));
        }

        container->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));
        container->SetMinHeight(m_minHeight);

        ComPtr<AdaptiveBackgroundImage> adaptiveBackgroundImage = PeekInnards<AdaptiveBackgroundImage>(m_backgroundImage);
        std::shared_ptr<AdaptiveCards::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && SUCCEEDED(adaptiveBackgroundImage->GetSharedModel(sharedBackgroundImage)))
        {
            container->SetBackgroundImage(std::move(sharedBackgroundImage));
        }

        container->SetBleed(m_bleed);

        std::optional<bool> rtl;
        if (m_rtl)
        {
            boolean rtlValue;
            RETURN_IF_FAILED(m_rtl->get_Value(&rtlValue));
            rtl = rtlValue;
        }
        container->SetRtl(rtl);

        GenerateSharedElements(m_items.Get(), container->GetItems());

        sharedModel = std::move(container);
        return S_OK;
    }
    CATCH_RETURN;
}
