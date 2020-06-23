// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSubmitAction.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::SubmitAction> submitAction =
            std::make_shared<AdaptiveSharedNamespace::SubmitAction>();
        return RuntimeClassInitialize(submitAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::SubmitAction>& sharedSubmitAction)
    try
    {
        if (sharedSubmitAction == nullptr)
        {
            return E_INVALIDARG;
        }

        auto sharedJson = sharedSubmitAction->GetDataJson();
        if (!sharedJson.empty())
        {
            RETURN_IF_FAILED(StringToJsonValue(sharedSubmitAction->GetDataJson(), &m_dataJson));
        }

        m_ignoreInputValidation = sharedSubmitAction->GetIgnoreInputValidation();

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedSubmitAction));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveSubmitAction::get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::Submit;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::get_DataJson(_COM_Outptr_ IJsonValue** data) { return m_dataJson.CopyTo(data); }

    HRESULT AdaptiveSubmitAction::put_DataJson(_In_ IJsonValue* data)
    {
        m_dataJson = data;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::get_IgnoreInputValidation(boolean* ignoreInputValidation)
    {
        *ignoreInputValidation = m_ignoreInputValidation;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::put_IgnoreInputValidation(boolean ignoreInputValidation)
    {
        m_ignoreInputValidation = ignoreInputValidation;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::SubmitAction> submitAction =
            std::make_shared<AdaptiveSharedNamespace::SubmitAction>();
        RETURN_IF_FAILED(CopySharedElementProperties(*submitAction));

        std::string jsonAsString;
        if (m_dataJson != nullptr)
        {
            RETURN_IF_FAILED(JsonValueToString(m_dataJson.Get(), jsonAsString));
            submitAction->SetDataJson(jsonAsString);
        }

        submitAction->SetIgnoreInputValidation(m_ignoreInputValidation);

        sharedModel = submitAction;
        return S_OK;
    }
    CATCH_RETURN;
}
