// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveOpenUrlAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveOpenUrlAction::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction> openUrlAction =
            std::make_shared<AdaptiveSharedNamespace::OpenUrlAction>();
        return RuntimeClassInitialize(openUrlAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveOpenUrlAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction>& sharedOpenUrlAction) try
    {
        if (sharedOpenUrlAction == nullptr)
        {
            return E_INVALIDARG;
        }

        ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), &uriActivationFactory));
        HString asHstring;
        RETURN_IF_FAILED(UTF8ToHString(sharedOpenUrlAction->GetUrl(), asHstring.GetAddressOf()));

        if (asHstring.IsValid())
        {
            RETURN_IF_FAILED(uriActivationFactory->CreateUri(asHstring.Get(), m_url.GetAddressOf()));
        }

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedOpenUrlAction));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveOpenUrlAction::get_Url(_COM_Outptr_ IUriRuntimeClass** url) { return m_url.CopyTo(url); }

    HRESULT AdaptiveOpenUrlAction::put_Url(_In_ IUriRuntimeClass* url) try
    {
        m_url = url;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveOpenUrlAction::get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::OpenUrl;
        return S_OK;
    }

    HRESULT AdaptiveOpenUrlAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction> openUrlAction =
            std::make_shared<AdaptiveSharedNamespace::OpenUrlAction>();
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
    }
    CATCH_RETURN;
}
