// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveAuthentication.h"
#include "AdaptiveTokenExchangeResource.h"
#include "AdaptiveAuthCardButton.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    AdaptiveAuthentication::AdaptiveAuthentication(const std::shared_ptr<::AdaptiveCards::Authentication>& sharedAuthentication)
    {
        Text = UTF8ToHString(sharedAuthentication->GetText());
        ConnectionName = UTF8ToHString(sharedAuthentication->GetConnectionName());

        if (auto tokenExchangeResource = sharedAuthentication->GetTokenExchangeResource())
        {
            TokenExchangeResource =
                *winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTokenExchangeResource>(
                    tokenExchangeResource);
        }

        std::vector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveAuthCardButton> buttons;
        for (auto& button : sharedAuthentication->GetButtons())
        {
            auto newShared =
                winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveAuthCardButton>(button);
            buttons.push_back(*newShared);
        }

        Buttons = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveAuthCardButton>(std::move(buttons));
    }

    std::shared_ptr<::AdaptiveCards::Authentication> AdaptiveAuthentication::GetSharedModel()
    {
        auto authentication = std::make_shared<::AdaptiveCards::Authentication>();
        authentication->SetText(HStringToUTF8(Text));
        authentication->SetConnectionName(HStringToUTF8(ConnectionName));

        if (auto resource = peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTokenExchangeResource>(TokenExchangeResource.get()))
        {
            authentication->SetTokenExchangeResource(resource->GetSharedModel());
        }

        for (auto&& button : Buttons.get())
        {
            auto impl = peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveAuthCardButton>(button);
            auto sharedAuthCardButton = impl->GetSharedModel();
            authentication->GetButtons().emplace_back(std::AdaptivePointerCast<::AdaptiveCards::AuthCardButton>(sharedAuthCardButton));
        }

        return authentication;
    }
}
