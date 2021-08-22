// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveCard.h"
#include "AdaptiveShowCardAction.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ShowCardAction> showCardAction = std::make_shared<AdaptiveCards::ShowCardAction>();
        return RuntimeClassInitialize(showCardAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedShowCardAction)
    try
    {
        if (sharedShowCardAction == nullptr)
        {
            return E_INVALIDARG;
        }

        if (auto card = sharedShowCardAction->GetCard())
        {
            m_card = *winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveCard>(card);
        }

        InitializeBaseElement(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(sharedShowCardAction));
        return S_OK;
    }
    CATCH_RETURN;

    IFACEMETHODIMP AdaptiveShowCardAction::get_Card(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard** card)
    {
        copy_to_abi(m_card, card);
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveShowCardAction::put_Card(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* card)
    {
        m_card = copy_from_abi<decltype(m_card)>(card);
        return S_OK;
    }

    HRESULT AdaptiveShowCardAction::get_ActionType(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType::ShowCard;
        return S_OK;
    }

    std::shared_ptr<AdaptiveCards::BaseActionElement> AdaptiveShowCardAction::GetSharedModel()
    {
        auto showCardAction = std::make_shared<AdaptiveCards::ShowCardAction>();
        THROW_IF_FAILED(CopySharedElementProperties(*showCardAction));

        auto card = peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveCard>(m_card);
        showCardAction->SetCard(card->GetSharedModel());

        return showCardAction;
    }
}
