// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveCard.h"
#include "AdaptiveShowCardAction.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction> showCardAction =
            std::make_shared<AdaptiveSharedNamespace::ShowCardAction>();
        return RuntimeClassInitialize(showCardAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction>& sharedShowCardAction)
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

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedShowCardAction));
        return S_OK;
    }
    CATCH_RETURN;

    IFACEMETHODIMP AdaptiveShowCardAction::get_Card(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCard** card)
    {
        return m_card.CopyTo(card);
    }

    IFACEMETHODIMP AdaptiveShowCardAction::put_Card(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* card)
    {
        m_card = card;
        return S_OK;
    }

    HRESULT AdaptiveShowCardAction::get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::ShowCard;
        return S_OK;
    }

    HRESULT AdaptiveShowCardAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction> showCardAction =
            std::make_shared<AdaptiveSharedNamespace::ShowCardAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(showCardAction)));

        ComPtr<AdaptiveNamespace::AdaptiveCard> card = PeekInnards<AdaptiveNamespace::AdaptiveCard>(m_card);

        std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> sharedCard;
        RETURN_IF_FAILED(card->GetSharedModel(sharedCard));

        showCardAction->SetCard(sharedCard);

        sharedModel = showCardAction;
        return S_OK;
    }
    CATCH_RETURN;
}
