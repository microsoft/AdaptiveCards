#include "pch.h"
#include "AdaptiveSubmitAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize() noexcept try
    {
        m_sharedSubmitAction = std::make_shared<SubmitAction>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::SubmitAction>& sharedSubmitAction)
    {
        m_sharedSubmitAction = sharedSubmitAction;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedSubmitAction->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedSubmitAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_ActionType(ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::XamlCardRenderer::ActionType::Submit;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedSubmitAction->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedSubmitAction->SetSpeak(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveSubmitAction::get_DataJson(HSTRING* data)
    {
        return UTF8ToHString(m_sharedSubmitAction->GetDataJson(), data);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveSubmitAction::put_DataJson(HSTRING data)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(data, out));
        m_sharedSubmitAction->SetDataJson(out);
        return S_OK;
    }
}}
