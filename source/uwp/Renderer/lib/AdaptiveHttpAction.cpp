#include "pch.h"

#include "AdaptiveHttpAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;

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
    HRESULT AdaptiveHttpAction::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedHttpAction->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedHttpAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::get_Url(IUriRuntimeClass** url)
    {
        *url = nullptr;

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        HSTRING imageUri;
        RETURN_IF_FAILED(UTF8ToHString(m_sharedHttpAction->GetUrl(), &imageUri));
        RETURN_IF_FAILED(uriActivationFactory->CreateUri(imageUri, url));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::put_Url(IUriRuntimeClass* url) try
    {
        if (url == nullptr)
        {
            return E_INVALIDARG;
        }

        HString urlTemp;
        url->get_AbsoluteUri(urlTemp.GetAddressOf());

        std::string urlString;
        RETURN_IF_FAILED(HStringToUTF8(urlTemp.Get(), urlString));
        m_sharedHttpAction->SetUrl(urlString);

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::get_Body(HSTRING* body)
    {
        return UTF8ToHString(m_sharedHttpAction->GetBody(), body);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::put_Body(HSTRING body)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(body, out));
        m_sharedHttpAction->SetBody(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::get_Method(HSTRING* method)
    {
        return UTF8ToHString(m_sharedHttpAction->GetMethod(), method);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHttpAction::put_Method(HSTRING method)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(method, out));
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
