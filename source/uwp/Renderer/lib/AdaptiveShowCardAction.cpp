#include "pch.h"
#include "AdaptiveShowCardAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize() noexcept try
    {
        m_sharedShowCardAction = std::make_shared<ShowCardAction>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedShowCardAction)
    {
        m_sharedShowCardAction = sharedShowCardAction;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedShowCardAction->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedShowCardAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_ActionType(ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::XamlCardRenderer::ActionType::ShowCard;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedShowCardAction->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedShowCardAction->SetSpeak(out);
        return S_OK;
    }
}}
