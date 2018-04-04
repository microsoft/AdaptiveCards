#include "pch.h"
#include "AdaptiveCard.h"
#include "AdaptiveShowCardAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction> showCardAction = std::make_shared<AdaptiveSharedNamespace::ShowCardAction>();
        return RuntimeClassInitialize(showCardAction);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction>& sharedShowCardAction) try
    {
        if (sharedShowCardAction == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCard>(&m_card, sharedShowCardAction->GetCard()));

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedShowCardAction));
        return S_OK;
    } CATCH_RETURN;

    IFACEMETHODIMP AdaptiveShowCardAction::get_Card(ABI::AdaptiveNamespace::IAdaptiveCard** card)
    {
        return m_card.CopyTo(card);
    }

    IFACEMETHODIMP AdaptiveShowCardAction::put_Card(ABI::AdaptiveNamespace::IAdaptiveCard* card)
    {
        m_card = card;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_ActionType(ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::ShowCard;
        return S_OK;
    }

    HRESULT AdaptiveShowCardAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction> showCardAction = std::make_shared<AdaptiveSharedNamespace::ShowCardAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(showCardAction)));

        ComPtr<AdaptiveNamespace::AdaptiveCard> card = PeekInnards<AdaptiveNamespace::AdaptiveCard>(m_card);

        std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> sharedCard;
        RETURN_IF_FAILED(card->GetSharedModel(sharedCard));

        showCardAction->SetCard(sharedCard);
        
        sharedModel = showCardAction;
        return S_OK;
    } CATCH_RETURN;
AdaptiveNamespaceEnd
