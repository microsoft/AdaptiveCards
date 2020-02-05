// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveContainer.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveContainer::AdaptiveContainer() : m_bleedDirection(ABI::AdaptiveNamespace::BleedDirection::None)
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveContainer::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Container> container = std::make_shared<AdaptiveSharedNamespace::Container>();
        return RuntimeClassInitialize(container);
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainer::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Container>& sharedContainer)
    try
    {
        if (sharedContainer == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateContainedElementsProjection(sharedContainer->GetItems(), m_items.Get());
        GenerateActionProjection(sharedContainer->GetSelectAction(), &m_selectAction);
        m_style = static_cast<ABI::AdaptiveNamespace::ContainerStyle>(sharedContainer->GetStyle());
        m_verticalAlignment =
            static_cast<ABI::AdaptiveNamespace::VerticalContentAlignment>(sharedContainer->GetVerticalContentAlignment());
        m_minHeight = sharedContainer->GetMinHeight();
        m_bleed = sharedContainer->GetBleed();
        m_bleedDirection = static_cast<ABI::AdaptiveNamespace::BleedDirection>(sharedContainer->GetBleedDirection());

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

    HRESULT AdaptiveContainer::get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_Style(ABI::AdaptiveNamespace::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_VerticalContentAlignment(_Out_ ABI::AdaptiveNamespace::VerticalContentAlignment* verticalAlignment)
    {
        *verticalAlignment = m_verticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_VerticalContentAlignment(ABI::AdaptiveNamespace::VerticalContentAlignment verticalAlignment)
    {
        m_verticalAlignment = verticalAlignment;
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

    HRESULT AdaptiveContainer::get_BleedDirection(ABI::AdaptiveNamespace::BleedDirection* bleedDirection)
    {
        // TODO: Current behavior is broken because it doesn't update when bleed updates. Unfortunately, neither does
        // the shared model logic.
        *bleedDirection = m_bleedDirection;
        return S_OK;
    }

    HRESULT AdaptiveContainer::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Container> container = std::make_shared<AdaptiveSharedNamespace::Container>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(container)));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            container->SetSelectAction(sharedAction);
        }

        container->SetStyle(static_cast<AdaptiveSharedNamespace::ContainerStyle>(m_style));
        container->SetVerticalContentAlignment(static_cast<AdaptiveSharedNamespace::VerticalContentAlignment>(m_verticalAlignment));
        container->SetMinHeight(m_minHeight);

        ComPtr<AdaptiveBackgroundImage> adaptiveBackgroundImage = PeekInnards<AdaptiveBackgroundImage>(m_backgroundImage);
        std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && SUCCEEDED(adaptiveBackgroundImage->GetSharedModel(sharedBackgroundImage)))
        {
            container->SetBackgroundImage(sharedBackgroundImage);
        }

        container->SetBleed(m_bleed);

        GenerateSharedElements(m_items.Get(), container->GetItems());

        sharedModel = container;
        return S_OK;
    }
    CATCH_RETURN;
}
