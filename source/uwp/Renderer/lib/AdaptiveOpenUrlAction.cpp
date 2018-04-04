#include "pch.h"
#include "AdaptiveOpenUrlAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

AdaptiveNamespaceStart
    HRESULT AdaptiveOpenUrlAction::RuntimeClassInitialize() noexcept try
    {
        m_sharedOpenUrlAction = std::make_shared<OpenUrlAction>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction>& sharedOpenUrlAction)
    {
        if (sharedOpenUrlAction == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedOpenUrlAction = sharedOpenUrlAction;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedOpenUrlAction->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedOpenUrlAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_Url(IUriRuntimeClass** url)
    {
        *url = nullptr;

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));

        std::wstring imageUri = StringToWstring(m_sharedOpenUrlAction->GetUrl());
        RETURN_IF_FAILED(uriActivationFactory->CreateUri(HStringReference(imageUri.c_str()).Get(), url));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::put_Url(IUriRuntimeClass* url) try
    {
        if (url == nullptr)
        {
            return E_INVALIDARG;
        }

        HString urlTemp;
        url->get_AbsoluteUri(urlTemp.GetAddressOf());

        std::string urlString;
        RETURN_IF_FAILED(HStringToUTF8(urlTemp.Get(), urlString));
        m_sharedOpenUrlAction->SetUrl(urlString);

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_ActionType(ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::OpenUrl;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedOpenUrlAction->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedOpenUrlAction->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_ActionTypeString(HSTRING* type)
    {
        ::ActionType typeEnum;
        RETURN_IF_FAILED(get_ActionType(&typeEnum));
        return ProjectedActionTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return JsonCppToJsonObject(m_sharedOpenUrlAction->GetAdditionalProperties(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        Json::Value jsonCpp;
        RETURN_IF_FAILED(JsonObjectToJsonCpp(jsonObject, &jsonCpp));
        m_sharedOpenUrlAction->SetAdditionalProperties(jsonCpp);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return StringToJsonObject(m_sharedOpenUrlAction->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction>& sharedModel)
    {
        sharedModel = m_sharedOpenUrlAction;
        return S_OK;
    }
AdaptiveNamespaceEnd
