// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveExecuteAction.h"
#include "AdaptiveExecuteAction.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveExecuteAction::AdaptiveExecuteAction(std::shared_ptr<::AdaptiveCards::ExecuteAction> const& sharedExecuteAction) :
        DataJson{nullptr}
    {
        auto sharedJson = sharedExecuteAction->GetDataJson();
        if (!sharedJson.empty())
        {
            DataJson = StringToJsonValue(sharedJson);
        }

        AssociatedInputs = static_cast<Uwp::AssociatedInputs>(sharedExecuteAction->GetAssociatedInputs());
        Verb = UTF8ToHString(sharedExecuteAction->GetVerb());

        InitializeBaseElement(sharedExecuteAction);
    }

    std::shared_ptr<::AdaptiveCards::BaseActionElement> AdaptiveExecuteAction::GetSharedModel()
    {
        auto executeAction = std::make_shared<::AdaptiveCards::ExecuteAction>();
        CopySharedElementProperties(*executeAction);

        if (DataJson.get())
        {
            executeAction->SetDataJson(JsonValueToString(DataJson));
        }

        executeAction->SetAssociatedInputs(static_cast<::AdaptiveCards::AssociatedInputs>(AssociatedInputs.get()));
        executeAction->SetVerb(HStringToUTF8(Verb));

        return executeAction;
    }
}
