// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "InputValue.h"
#include "AdaptiveInputs.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveInputs : AdaptiveInputsT<AdaptiveInputs>
    {
        AdaptiveInputs() = default;

        // IAdaptiveInputs
        winrt::Windows::Data::Json::JsonObject AsJson();
        winrt::Windows::Foundation::Collections::ValueSet AsValueSet();

        bool ValidateInputs(ObjectModel::Uwp::IAdaptiveActionElement const& submitAction);

        void AddInputValue(Uwp::IAdaptiveInputValue const& inputValue, _In_ Uwp::AdaptiveRenderArgs const& renderArgs);
        void LinkSubmitActionToCard(ObjectModel::Uwp::IAdaptiveActionElement const& action, Uwp::AdaptiveRenderArgs const& renderArgs);
        void LinkCardToParent(uint32_t cardId, uint32_t parentCardId);

        Uwp::IAdaptiveInputValue GetInputValue(ObjectModel::Uwp::IAdaptiveInputElement const& inputElement);

    private:
        std::string GetInputItemsAsJsonString();
        std::vector<Uwp::IAdaptiveInputValue> GetInputsToValidate(ObjectModel::Uwp::IAdaptiveActionElement const& submitAction);
        uint32_t GetInternalIdFromAction(ObjectModel::Uwp::IAdaptiveActionElement const& action);

        // Map with key: input id, value: input value class
        // This one has the collection of all input element values, this was introduced to be able to set the error
        // message to the input value and at the same time, being able to respect custom inputs having error messages
        std::unordered_map<std::string, Uwp::IAdaptiveInputValue> m_inputValues;

        // This is cache of the last inputs that were retrieved for validation (and succeeded)
        // This is needed as the AsJson and AsValueSet methods are called after validating but we don't get an action reference to rebuild the list
        std::vector<Uwp::IAdaptiveInputValue> m_lastRetrievedValues;

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
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveInputs : AdaptiveInputsT<AdaptiveInputs, implementation::AdaptiveInputs>
    {
    };
}
