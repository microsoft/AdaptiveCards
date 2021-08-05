// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSubmitAction.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::SubmitAction> submitAction = std::make_shared<AdaptiveCards::SubmitAction>();
        return RuntimeClassInitialize(submitAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::SubmitAction>& sharedSubmitAction)
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

        m_associatedInputs =
            static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::AssociatedInputs>(sharedSubmitAction->GetAssociatedInputs());

        InitializeBaseElement(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(sharedSubmitAction));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveSubmitAction::get_ActionType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::Submit;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::get_DataJson(_COM_Outptr_ IJsonValue** data) { return m_dataJson.CopyTo(data); }

    HRESULT AdaptiveSubmitAction::put_DataJson(_In_ IJsonValue* data)
    {
        m_dataJson = data;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::get_AssociatedInputs(ABI::AdaptiveCards::ObjectModel::Uwp::AssociatedInputs* associatedInputs)
    {
        *associatedInputs = m_associatedInputs;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::put_AssociatedInputs(ABI::AdaptiveCards::ObjectModel::Uwp::AssociatedInputs associatedInputs)
    {
        m_associatedInputs = associatedInputs;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::SubmitAction> submitAction = std::make_shared<AdaptiveCards::SubmitAction>();
        RETURN_IF_FAILED(CopySharedElementProperties(*submitAction));

        std::string jsonAsString;
        if (m_dataJson != nullptr)
        {
            RETURN_IF_FAILED(JsonValueToString(m_dataJson.Get(), jsonAsString));
            submitAction->SetDataJson(std::move(jsonAsString));
        }

        submitAction->SetAssociatedInputs(static_cast<AdaptiveCards::AssociatedInputs>(m_associatedInputs));

        sharedModel = std::move(submitAction);
        return S_OK;
    }
    CATCH_RETURN;
}
