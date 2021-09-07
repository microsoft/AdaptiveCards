// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSubmitAction.h"
#include "AdaptiveSubmitAction.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveSubmitAction::AdaptiveSubmitAction(const std::shared_ptr<::AdaptiveCards::SubmitAction>& sharedSubmitAction)
    {
        auto sharedJson = sharedSubmitAction->GetDataJson();
        if (!sharedJson.empty())
        {
            DataJson = StringToJsonValue(sharedJson);
        }

        AssociatedInputs = static_cast<Uwp::AssociatedInputs>(sharedSubmitAction->GetAssociatedInputs());

        InitializeBaseElement(sharedSubmitAction);
    }

    std::shared_ptr<::AdaptiveCards::BaseActionElement> AdaptiveSubmitAction::GetSharedModel()
    {
        auto submitAction = std::make_shared<::AdaptiveCards::SubmitAction>();
        CopySharedElementProperties(*submitAction);

        if (DataJson.get())
        {
            submitAction->SetDataJson(JsonValueToString(DataJson));
        }

        submitAction->SetAssociatedInputs(static_cast<::AdaptiveCards::AssociatedInputs>(AssociatedInputs.get()));
        return submitAction;
    }
}
