#include "pch.h"
#include "AdaptiveHttpAction.h"
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
    HRESULT AdaptiveHttpAction::RuntimeClassInitialize() noexcept try
    {
        m_sharedHttpAction = std::make_shared<HttpAction>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::HttpAction>& sharedHttpAction)
    {
        m_sharedHttpAction = sharedHttpAction;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::get_Title(HSTRING* text)
    {
        return UTF8ToHString(m_sharedHttpAction->GetTitle(), text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::put_Title(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedHttpAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::get_Url(HSTRING* text)
    {
        return UTF8ToHString(m_sharedHttpAction->GetUrl(), text);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::put_Url(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedHttpAction->SetUrl(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::get_Body(HSTRING* text)
    {
        return UTF8ToHString(m_sharedHttpAction->GetBody(), text);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::put_Body(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedHttpAction->SetBody(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::get_Method(HSTRING* text)
    {
        return UTF8ToHString(m_sharedHttpAction->GetMethod(), text);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::put_Method(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedHttpAction->SetMethod(out);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::get_ActionType(ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::XamlCardRenderer::ActionType::Http;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedHttpAction->GetSpeak(), speak);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveHttpAction::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedHttpAction->SetSpeak(out);
        return S_OK;
    }
}}
