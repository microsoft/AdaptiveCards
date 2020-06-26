// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "InputValue.h"

namespace AdaptiveNamespace
{
    class AdaptiveInputs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveInputs>
    {
        AdaptiveRuntime(AdaptiveInputs);

    public:
        AdaptiveInputs();
        HRESULT RuntimeClassInitialize() noexcept;

        // IAdaptiveInputs
        IFACEMETHODIMP AsJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** value);
        IFACEMETHODIMP AsValueSet(_COM_Outptr_ ABI::Windows::Foundation::Collections::IPropertySet** value);

        IFACEMETHODIMP ValidateInputs(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction, boolean* inputsAreValid);

        HRESULT AddInputValue(_In_ ABI::AdaptiveNamespace::IAdaptiveInputValue* inputValue, _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);
        HRESULT LinkSubmitActionToCard(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction, _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);
        HRESULT LinkCardToParent(_In_ InternalId cardId, _In_ InternalId parentCardId);

        HRESULT GetInputValue(_In_ ABI::AdaptiveNamespace::IAdaptiveInputElement* inputElement,
                              _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputValue** inputValue);

    private:
        std::string GetInputItemsAsJsonString();
        void GetInputsToValidate(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction,
                                 _Out_ std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>>& inputs);
        void GetAllInputs(_Out_ std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>>& inputs);

        // Map with key: input internal id, value: input value class
        // This one has the collection of all input element values, this was introduced to be able to set the error message to the input value
        // and at the same time, being able to respect custom inputs having error messages
        std::unordered_map<std::size_t, Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>> m_inputValues;

        // This is cache of the last inputs that were retrieved for validation (and succeeded)
        // This is needed as the AsJson and AsValueSet methods are called after validating but we don't get an action reference to rebuild the list
        std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>> m_lastRetrievedValues;

        // Map with key: internal id of card, value: internal id of parent card
        // This map allows us to move vertically accross the cards to retrieve the inputs
        std::unordered_map<std::size_t, std::size_t> m_parentCard;

        // Map with key: internal id for submit action, value: internal id of card that contains the action
        // This is needed so we can get a starting point from where to start retrieving inputs
        std::unordered_map<std::size_t, std::size_t> m_containerCardForAction;

        // Map with key: internal id for container card, value: vector of the internal ids of the inputs in the card
        // This is needed to retrieve inputs once we know what cards to look into
        std::unordered_map<std::size_t, std::vector<std::size_t>> m_inputsPerCard;
    };

    ActivatableClass(AdaptiveInputs);
}
