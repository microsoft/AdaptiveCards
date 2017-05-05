#include "pch.h"
#include "AdaptiveOpenUrlAction.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveOpenUrlAction::RuntimeClassInitialize() noexcept try
    {
        m_sharedOpenUrlAction = std::make_shared<OpenUrlAction>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::OpenUrlAction>& sharedOpenUrlAction)
    {
        m_sharedOpenUrlAction = sharedOpenUrlAction;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_Title(HSTRING* text)
    {
        return UTF8ToHString(m_sharedOpenUrlAction->GetTitle(), text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::put_Title(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedOpenUrlAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveOpenUrlAction::get_Url(HSTRING* text)
    {
        return UTF8ToHString(m_sharedOpenUrlAction->GetUrl(), text);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveOpenUrlAction::put_Url(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedOpenUrlAction->SetUrl(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveOpenUrlAction::get_ActionType(ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::XamlCardRenderer::ActionType::OpenUrl;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveOpenUrlAction::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedOpenUrlAction->GetSpeak(), speak);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveOpenUrlAction::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedOpenUrlAction->SetSpeak(out);
        return S_OK;
    }
}}
