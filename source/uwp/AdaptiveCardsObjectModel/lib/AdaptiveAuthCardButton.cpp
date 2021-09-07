// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveAuthCardButton.h"
#include "AdaptiveAuthCardButton.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveAuthCardButton::AdaptiveAuthCardButton(std::shared_ptr<::AdaptiveCards::AuthCardButton> const& sharedAuthCardButton)
    {
        Type = UTF8ToHString(sharedAuthCardButton->GetType());
        Title = UTF8ToHString(sharedAuthCardButton->GetTitle());
        Image = UTF8ToHString(sharedAuthCardButton->GetImage());
        Value = UTF8ToHString(sharedAuthCardButton->GetValue());
    }

    std::shared_ptr<::AdaptiveCards::AuthCardButton> AdaptiveAuthCardButton::GetSharedModel()
    {
        auto authCardButton = std::make_shared<::AdaptiveCards::AuthCardButton>();
        authCardButton->SetType(HStringToUTF8(Type));
        authCardButton->SetTitle(HStringToUTF8(Title));
        authCardButton->SetImage(HStringToUTF8(Image));
        authCardButton->SetValue(HStringToUTF8(Value));
        return authCardButton;
    }

}
