// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveColumnSet.h"
#include "AdaptiveColumnSet.g.cpp"

#include <windows.foundation.collections.h>
#include "AdaptiveColumn.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    AdaptiveColumnSet::AdaptiveColumnSet(std::shared_ptr<::AdaptiveCards::ColumnSet> const& sharedColumnSet)
    {
        Columns = GenerateVectorProjection<implementation::AdaptiveColumn>(sharedColumnSet->GetColumns());
        SelectAction = GenerateActionProjection(sharedColumnSet->GetSelectAction());
        Style = static_cast<Xaml_OM::ContainerStyle>(sharedColumnSet->GetStyle());
        MinHeight = sharedColumnSet->GetMinHeight();
        Bleed = sharedColumnSet->GetBleed();
        BleedDirection = static_cast<Xaml_OM::BleedDirection>(sharedColumnSet->GetBleedDirection());
        HorizontalAlignment = opt_cast<Xaml_OM::HAlignment>(sharedColumnSet->GetHorizontalAlignment());
        InitializeBaseElement(sharedColumnSet);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveColumnSet::GetSharedModel()
    {
        auto columnSet = std::make_shared<::AdaptiveCards::ColumnSet>();
        CopySharedElementProperties(*columnSet);

        if (SelectAction.get())
        {
            columnSet->SetSelectAction(GenerateSharedAction(SelectAction.get()));
        }

        if (HorizontalAlignment)
        {
            columnSet->SetHorizontalAlignment(HorizontalAlignment.get<::AdaptiveCards::HorizontalAlignment>());
        }

        columnSet->GetColumns() = GenerateSharedVector<implementation::AdaptiveColumn, ::AdaptiveCards::Column>(Columns.get());
        columnSet->SetStyle(static_cast<::AdaptiveCards::ContainerStyle>(Style.get()));
        columnSet->SetMinHeight(MinHeight.get());
        columnSet->SetBleed(Bleed.get());

        return columnSet;
    }
}
