// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveCard.h"
#include "AdaptiveShowCardAction.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
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

        std::shared_ptr<AdaptiveCards::AdaptiveCard> card = sharedShowCardAction->GetCard();
        if (card != nullptr)
        {
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCard>(&m_card, sharedShowCardAction->GetCard()));
        }

        InitializeBaseElement(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(sharedShowCardAction));
        return S_OK;
    }
    CATCH_RETURN;

    IFACEMETHODIMP AdaptiveShowCardAction::get_Card(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard** card)
    {
        return m_card.CopyTo(card);
    }

    IFACEMETHODIMP AdaptiveShowCardAction::put_Card(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* card)
    {
        m_card = card;
        return S_OK;
    }

    HRESULT AdaptiveShowCardAction::get_ActionType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::ShowCard;
        return S_OK;
    }

    HRESULT AdaptiveShowCardAction::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::ShowCardAction> showCardAction = std::make_shared<AdaptiveCards::ShowCardAction>();
        RETURN_IF_FAILED(CopySharedElementProperties(*showCardAction));

        ComPtr<AdaptiveCards::ObjectModel::Uwp::AdaptiveCard> card =
            PeekInnards<AdaptiveCards::ObjectModel::Uwp::AdaptiveCard>(m_card);

        std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedCard;
        RETURN_IF_FAILED(card->GetSharedModel(sharedCard));

        showCardAction->SetCard(std::move(sharedCard));

        sharedModel = std::move(showCardAction);
        return S_OK;
    }
    CATCH_RETURN;
}
