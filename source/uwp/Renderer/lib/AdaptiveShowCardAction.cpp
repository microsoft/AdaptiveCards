#include "pch.h"
#include "AdaptiveCard.h"
#include "AdaptiveShowCardAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::ShowCardAction> showCardAction = std::make_shared<AdaptiveCards::ShowCardAction>();
        return RuntimeClassInitialize(showCardAction);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedShowCardAction) try
    {
        if (sharedShowCardAction == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCard>(&m_card, sharedShowCardAction->GetCard()));

        InitializeBaseElement(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(sharedShowCardAction));
        return S_OK;
    } CATCH_RETURN;

    IFACEMETHODIMP AdaptiveShowCardAction::get_Card(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard** card)
    {
        return m_card.CopyTo(card);
    }

    IFACEMETHODIMP AdaptiveShowCardAction::put_Card(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard* card)
    {
        m_card = card;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_ActionType(ABI::AdaptiveCards::Rendering::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::Rendering::Uwp::ActionType::ShowCard;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::ShowCardAction> showCardAction = std::make_shared<AdaptiveCards::ShowCardAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(showCardAction)));

        ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveCard> card = PeekInnards<AdaptiveCards::Rendering::Uwp::AdaptiveCard>(m_card);

        std::shared_ptr<AdaptiveCards::AdaptiveCard> sharedCard;
        RETURN_IF_FAILED(card->GetSharedModel(sharedCard));

        showCardAction->SetCard(sharedCard);
        
        sharedModel = showCardAction;
        return S_OK;
    } CATCH_RETURN;
}}}
