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
        std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction> openUrlAction = std::make_shared<AdaptiveSharedNamespace::OpenUrlAction>();
        return RuntimeClassInitialize(openUrlAction);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction>& sharedOpenUrlAction) try
    {
        if (sharedOpenUrlAction == nullptr)
        {
            return E_INVALIDARG;
        }

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(),
            &uriActivationFactory));
        std::wstring imageUri = StringToWstring(sharedOpenUrlAction->GetUrl());
        RETURN_IF_FAILED(uriActivationFactory->CreateUri(HStringReference(imageUri.c_str()).Get(), m_url.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedOpenUrlAction));
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_Url(IUriRuntimeClass** url)
    {
        return m_url.CopyTo(url);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::put_Url(IUriRuntimeClass* url) try
    {
        m_url = url;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveOpenUrlAction::get_ActionType(ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::OpenUrl;
        return S_OK;
    }

    HRESULT AdaptiveOpenUrlAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction> openUrlAction = std::make_shared<AdaptiveSharedNamespace::OpenUrlAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(openUrlAction)));

        if (m_url != nullptr)
        {
            HString urlTemp;
            m_url->get_AbsoluteUri(urlTemp.GetAddressOf());

            std::string urlString;
            RETURN_IF_FAILED(HStringToUTF8(urlTemp.Get(), urlString));
            openUrlAction->SetUrl(urlString);
        }

        sharedModel = openUrlAction;
        return S_OK;
    } CATCH_RETURN;
AdaptiveNamespaceEnd
