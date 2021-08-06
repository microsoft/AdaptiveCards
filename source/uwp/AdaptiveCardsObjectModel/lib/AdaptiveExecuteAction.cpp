// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveExecuteAction.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveExecuteAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ExecuteAction> executeAction = std::make_shared<AdaptiveCards::ExecuteAction>();
        return RuntimeClassInitialize(executeAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveExecuteAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ExecuteAction>& sharedExecuteAction)
    try
    {
        auto sharedJson = sharedExecuteAction->GetDataJson();
        if (!sharedJson.empty())
        {
            RETURN_IF_FAILED(StringToJsonValue(sharedExecuteAction->GetDataJson(), &m_dataJson));
        }

        m_associatedInputs =
            static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::AssociatedInputs>(sharedExecuteAction->GetAssociatedInputs());

        RETURN_IF_FAILED(UTF8ToHString(sharedExecuteAction->GetVerb(), m_verb.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(sharedExecuteAction));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveExecuteAction::get_ActionType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::Execute;
        return S_OK;
    }

    HRESULT AdaptiveExecuteAction::get_DataJson(_COM_Outptr_ IJsonValue** data) { return m_dataJson.CopyTo(data); }

    HRESULT AdaptiveExecuteAction::put_DataJson(_In_ IJsonValue* data)
    {
        m_dataJson = data;
        return S_OK;
    }

    HRESULT AdaptiveExecuteAction::get_AssociatedInputs(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::AssociatedInputs* associatedInputs)
    {
        *associatedInputs = m_associatedInputs;
        return S_OK;
    }

    HRESULT AdaptiveExecuteAction::put_AssociatedInputs(ABI::AdaptiveCards::ObjectModel::Uwp::AssociatedInputs associatedInputs)
    {
        m_associatedInputs = associatedInputs;
        return S_OK;
    }

    HRESULT AdaptiveExecuteAction::get_Verb(_Outptr_ HSTRING* verb) { return m_verb.CopyTo(verb); }

    HRESULT AdaptiveExecuteAction::put_Verb(_In_ HSTRING verb) { return m_verb.Set(verb); }

    HRESULT AdaptiveExecuteAction::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::ExecuteAction> executeAction = std::make_shared<AdaptiveCards::ExecuteAction>();
        RETURN_IF_FAILED(CopySharedElementProperties(*executeAction));

        std::string jsonAsString;
        if (m_dataJson != nullptr)
        {
            RETURN_IF_FAILED(JsonValueToString(m_dataJson.Get(), jsonAsString));
            executeAction->SetDataJson(std::move(jsonAsString));
        }

        executeAction->SetAssociatedInputs(static_cast<AdaptiveCards::AssociatedInputs>(m_associatedInputs));

        std::string verb;
        RETURN_IF_FAILED(HStringToUTF8(m_verb.Get(), verb));
        executeAction->SetVerb(verb);

        sharedModel = std::move(executeAction);
        return S_OK;
    }
    CATCH_RETURN;
}
