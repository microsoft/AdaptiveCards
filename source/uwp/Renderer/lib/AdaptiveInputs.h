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

    private:
        std::string GetInputItemsAsJsonString();
        void GetInputsToValidate(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction,
                                 _Out_ std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>>& inputs);
        void GetAllInputs(_Out_ std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>>& inputs);

        std::unordered_map<std::size_t, std::vector<Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputValue>>> m_inputValues;
        std::unordered_map<std::size_t, std::size_t> m_parentCard;
        std::unordered_map<std::size_t, std::size_t> m_containerCardForAction;
    };

    ActivatableClass(AdaptiveInputs);
}
