// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveUnsupportedAction.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveUnsupportedAction::AdaptiveUnsupportedAction(const std::shared_ptr<::AdaptiveCards::UnknownAction>& sharedUnknown)
    {
        InitializeBaseElement(sharedUnknown);
    }

    std::shared_ptr<::AdaptiveCards::BaseActionElement> AdaptiveUnsupportedAction::GetSharedModel()
    {
        auto unknownAction = std::make_shared<::AdaptiveCards::UnknownAction>();
        unknownAction->SetElementTypeString(HStringToUTF8(ActionTypeString));
        CopySharedElementProperties(*unknownAction);

        return unknownAction;
    }
}
