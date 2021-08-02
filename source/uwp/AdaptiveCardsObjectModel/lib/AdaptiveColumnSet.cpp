// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveColumnSet.h"

#include "ObjectModelUtil.h"
#include "Vector.h"
#include <windows.foundation.collections.h>
#include "AdaptiveColumn.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveColumnSet::AdaptiveColumnSet() :
        m_bleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection::None)
    {
        m_columns = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveColumn*>>();
    }

    HRESULT AdaptiveColumnSet::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ColumnSet> columnSet = std::make_shared<AdaptiveCards::ColumnSet>();
        return RuntimeClassInitialize(columnSet);
    }
    CATCH_RETURN;

    HRESULT AdaptiveColumnSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ColumnSet>& sharedColumnSet) noexcept
    try
    {
        if (sharedColumnSet == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateColumnsProjection(sharedColumnSet->GetColumns(), m_columns.Get());
        GenerateActionProjection(sharedColumnSet->GetSelectAction(), &m_selectAction);

        m_style = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedColumnSet->GetStyle());
        m_minHeight = sharedColumnSet->GetMinHeight();
        m_bleed = sharedColumnSet->GetBleed();
        m_bleedDirection =
            static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection>(sharedColumnSet->GetBleedDirection());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedColumnSet));

        return S_OK;
    }
    CATCH_RETURN;

    IFACEMETHODIMP AdaptiveColumnSet::get_Columns(_COM_Outptr_ IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveColumn*>** columns)
    {
        return m_columns.CopyTo(columns);
    }

    IFACEMETHODIMP AdaptiveColumnSet::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    IFACEMETHODIMP AdaptiveColumnSet::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::get_MinHeight(_Out_ UINT32* minHeight)
    {
        *minHeight = m_minHeight;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::put_MinHeight(UINT32 minHeight)
    {
        m_minHeight = minHeight;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::get_Bleed(_Out_ boolean* isBleed)
    {
        *isBleed = m_bleed;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::put_Bleed(boolean isBleed)
    {
        m_bleed = isBleed;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::get_BleedDirection(ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection* bleedDirection)
    {
        // TODO: Current behavior is broken because it doesn't update when bleed updates. Unfortunately, neither does
        // the shared model logic. https://github.com/Microsoft/AdaptiveCards/issues/2678
        *bleedDirection = m_bleedDirection;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::ColumnSet;
        return S_OK;
    }

    HRESULT AdaptiveColumnSet::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ColumnSet> columnSet = std::make_shared<AdaptiveCards::ColumnSet>();
        RETURN_IF_FAILED(CopySharedElementProperties(*columnSet));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            columnSet->SetSelectAction(std::move(sharedAction));
        }

        GenerateSharedColumns(m_columns.Get(), columnSet->GetColumns());

        columnSet->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(m_style));
        columnSet->SetMinHeight(m_minHeight);
        columnSet->SetBleed(m_bleed);

        sharedModel = std::move(columnSet);
        return S_OK;
    }
    CATCH_RETURN;
}
