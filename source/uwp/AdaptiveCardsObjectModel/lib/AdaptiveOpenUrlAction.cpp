// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveOpenUrlAction.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveOpenUrlAction::AdaptiveOpenUrlAction(const std::shared_ptr<::AdaptiveCards::OpenUrlAction>& sharedOpenUrlAction)
    {
        if (!sharedOpenUrlAction->GetUrl().empty())
        {
            Url = winrt::Windows::Foundation::Uri{UTF8ToHString(sharedOpenUrlAction->GetUrl())};
        }

        InitializeBaseElement(sharedOpenUrlAction);
    }

    std::shared_ptr<::AdaptiveCards::BaseActionElement> AdaptiveOpenUrlAction::GetSharedModel()
    {
        auto openUrlAction = std::make_shared<::AdaptiveCards::OpenUrlAction>();
        CopySharedElementProperties(*openUrlAction);

        if (Url.get())
        {
            openUrlAction->SetUrl(HStringToUTF8(Url->AbsoluteUri()));
        }

        return openUrlAction;
    }
}
