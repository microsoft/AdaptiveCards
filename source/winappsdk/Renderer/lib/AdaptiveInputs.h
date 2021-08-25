// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "InputValue.h"
#include "AdaptiveInputs.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveInputs : AdaptiveInputsT<AdaptiveInputs>
    {
        AdaptiveInputs() = default;

        // IAdaptiveInputs
        winrt::Windows::Data::Json::JsonObject AsJson();
        winrt::Windows::Foundation::Collections::PropertySet AsValueSet();

        bool ValidateInputs(ObjectModel::WinUI3::IAdaptiveActionElement const& submitAction);

        HRESULT AddInputValue(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue* inputValue,
                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);
        HRESULT LinkSubmitActionToCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* submitAction,
                                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);
        HRESULT LinkCardToParent(UINT32 cardId, UINT32 parentCardId);

        HRESULT GetInputValue(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement* inputElement,
                              _COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue** inputValue);

    private:
        std::string GetInputItemsAsJsonString();
        std::vector<WinUI3::IAdaptiveInputValue> GetInputsToValidate(ObjectModel::WinUI3::IAdaptiveActionElement const& submitAction);
        void GetInputsToValidate(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* submitAction,
                                 _Out_ std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue>>& inputs);
        void GetAllInputs(_Out_ std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue>>& inputs);
        HRESULT AdaptiveInputs::GetInternalIdFromAction(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action,
                                                        _Out_ UINT32* actionInternalId);

        // Map with key: input id, value: input value class
        // This one has the collection of all input element values, this was introduced to be able to set the error
        // message to the input value and at the same time, being able to respect custom inputs having error messages
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue>> m_inputValues;

        // This is cache of the last inputs that were retrieved for validation (and succeeded)
        // This is needed as the AsJson and AsValueSet methods are called after validating but we don't get an action reference to rebuild the list
        std::vector<WinUI3::IAdaptiveInputValue> m_lastRetrievedValues;

        // Map with key: internal id of card, value: internal id of parent card
        // This map allows us to move vertically accross the cards to retrieve the inputs
        std::unordered_map<std::size_t, std::size_t> m_parentCard;

        // Map with key: internal id for submit action, value: internal id of card that contains the action
        // This is needed so we can get a starting point from where to start retrieving inputs
        std::unordered_map<std::size_t, std::size_t> m_containerCardForAction;

        // Map with key: internal id for container card, value: vector of the ids (element property) of the inputs in
        // the card This is needed to retrieve inputs once we know what cards to look into
        std::unordered_map<std::size_t, std::vector<std::string>> m_inputsPerCard;
    };

    ActivatableClass(AdaptiveInputs);
}
