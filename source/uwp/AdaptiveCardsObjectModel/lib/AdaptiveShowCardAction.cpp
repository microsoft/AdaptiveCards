// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveCard.h"
#include "AdaptiveShowCardAction.h"
#include "AdaptiveShowCardAction.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveShowCardAction::AdaptiveShowCardAction(const std::shared_ptr<::AdaptiveCards::ShowCardAction>& sharedShowCardAction)
    {
        if (auto card = sharedShowCardAction->GetCard())
        {
            Card = winrt::make<implementation::AdaptiveCard>(card);
        }

        InitializeBaseElement(sharedShowCardAction);
    }

    std::shared_ptr<::AdaptiveCards::BaseActionElement> AdaptiveShowCardAction::GetSharedModel()
    {
        auto showCardAction = std::make_shared<::AdaptiveCards::ShowCardAction>();
        CopySharedElementProperties(*showCardAction);

        showCardAction->SetCard(peek_innards<implementation::AdaptiveCard>(Card.get())->GetSharedModel());

        return showCardAction;
    }
}
