// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveInputs.h"
#include <uwp\Renderer\lib\AdaptiveActionElement.h>
#include <uwp\Renderer\lib\AdaptiveRenderArgs.h>
#include <uwp\Renderer\lib\AdaptiveCard.h>
#include "AdaptiveSubmitAction.h"
#include "AdaptiveInputElement.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveInputs::AdaptiveInputs() { }

    HRESULT AdaptiveInputs::RuntimeClassInitialize() noexcept
    {
        return S_OK;
    }

    HRESULT AdaptiveInputs::AsJson(_COM_Outptr_ IJsonObject** value)
    {
        return StringToJsonObject(GetInputItemsAsJsonString(), value);
    }

    HRESULT AdaptiveInputs::AddInputValue(_In_ IAdaptiveInputValue* inputValue, _In_ IAdaptiveRenderArgs* renderArgs)
    {
        ComPtr<IAdaptiveRenderArgs> localRenderArgs(renderArgs);

        ComPtr<IAdaptiveCard> parentCard;
        RETURN_IF_FAILED(localRenderArgs->get_ParentCard(parentCard.GetAddressOf()));
        ComPtr<AdaptiveCard> parentCardImpl = PeekInnards<AdaptiveNamespace::AdaptiveCard>(parentCard);
        InternalId cardId = parentCardImpl->GetInternalId();

        ComPtr<IAdaptiveInputElement> inputElement;
        RETURN_IF_FAILED(inputValue->get_InputElement(inputElement.GetAddressOf()));


        ComPtr<AdaptiveInputElementBase> cardElementImpl;
        RETURN_IF_FAILED(inputElement->QueryInterface(cardElementImpl.GetAddressOf()));

        // ComPtr<AdaptiveCardElementBase> inputElementImpl = PeekInnards<AdaptiveNamespace::AdaptiveCardElementBase>(inputElement);
        InternalId inputId = cardElementImpl->GetInternalId();
        std::size_t inputIdHash = inputId.Hash();

        m_inputsPerCard[cardId.Hash()].push_back(inputIdHash);
        m_inputValues[inputIdHash] = inputValue;
        return S_OK;
    }

    HRESULT AdaptiveInputs::LinkSubmitActionToCard(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction,
                                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs)
    {
        ComPtr<IAdaptiveSubmitAction> localSubmitAction(submitAction);
        ComPtr<AdaptiveNamespace::AdaptiveSubmitAction> submitActionImpl =
            PeekInnards<AdaptiveNamespace::AdaptiveSubmitAction>(localSubmitAction);
        InternalId actionId = submitActionImpl->GetInternalId();

        ComPtr<IAdaptiveRenderArgs> localRenderArgs(renderArgs);
        ComPtr<IAdaptiveCard> adaptiveCard;
        RETURN_IF_FAILED(localRenderArgs->get_ParentCard(adaptiveCard.GetAddressOf()));

        ComPtr<AdaptiveCard> adaptiveCardImpl = PeekInnards<AdaptiveNamespace::AdaptiveCard>(adaptiveCard);
        InternalId cardId = adaptiveCardImpl->GetInternalId();

        m_containerCardForAction[actionId.Hash()] = cardId.Hash();
        return S_OK;
    }

    HRESULT AdaptiveInputs::LinkCardToParent(_In_ InternalId cardId, _In_ InternalId parentCardId)
    {
        m_parentCard[cardId.Hash()] = parentCardId.Hash();
        return S_OK;
    }

    HRESULT AdaptiveInputs::GetInputValue(_In_ IAdaptiveInputElement* inputElement, IAdaptiveInputValue** inputValue)
    {
        ComPtr<IAdaptiveInputElement> localInputElement(inputElement);

        ComPtr<AdaptiveInputElementBase> inputElementImpl;
        RETURN_IF_FAILED(localInputElement->QueryInterface(inputElementImpl.GetAddressOf()));

        // ComPtr<AdaptiveInputElementBase> inputElementImpl = PeekInnards<AdaptiveNamespace::AdaptiveInputElementBase>(inputElement);
        InternalId inputId = inputElementImpl->GetInternalId();

        RETURN_IF_FAILED(m_inputValues[inputId.Hash()].CopyTo(inputValue));

        return S_OK;
    }

    std::string AdaptiveInputs::GetInputItemsAsJsonString()
    {
        Json::Value jsonValue;

        std::vector<ComPtr<IAdaptiveInputValue>> inputs;
        GetAllInputs(inputs);
        for (auto& inputValue : inputs)
        {
            ComPtr<IAdaptiveCardElement> cardElement;
            ComPtr<IAdaptiveInputElement> inputElement;
            THROW_IF_FAILED(inputValue->get_InputElement(&inputElement));
            THROW_IF_FAILED(inputElement.As(&cardElement));

            HString idString;
            THROW_IF_FAILED(cardElement->get_Id(idString.GetAddressOf()));
            std::string key = HStringToUTF8(idString.Get());

            HString inputStringValue;
            THROW_IF_FAILED(inputValue->get_CurrentValue(inputStringValue.GetAddressOf()));
            std::string value = HStringToUTF8(inputStringValue.Get());

            jsonValue[key] = value;
        }

        Json::StreamWriterBuilder writerBuilder;
        std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
        std::ostringstream outStream;
        writer->write(jsonValue, &outStream);
        return outStream.str();
    }

    HRESULT AdaptiveInputs::AsValueSet(_COM_Outptr_ IPropertySet** valueSetOut)
    {
        *valueSetOut = nullptr;
        ComPtr<IPropertySet> valueSet;
        RETURN_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Foundation_Collections_ValueSet).Get(), &valueSet));
        ComPtr<IMap<HSTRING, IInspectable*>> propertySetMap;
        RETURN_IF_FAILED(valueSet.As(&propertySetMap));

        ComPtr<IPropertyValueStatics> propertyValueFactory;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(),
                                              &propertyValueFactory));

        std::vector<ComPtr<IAdaptiveInputValue>> inputs;
        GetAllInputs(inputs);
        for (auto& inputValue : inputs)
        {
            ComPtr<IAdaptiveCardElement> cardElement;
            ComPtr<IAdaptiveInputElement> inputElement;
            THROW_IF_FAILED(inputValue->get_InputElement(&inputElement));
            THROW_IF_FAILED(inputElement.As(&cardElement));

            HString key;
            THROW_IF_FAILED(cardElement->get_Id(key.GetAddressOf()));

            HString value;
            RETURN_IF_FAILED(inputValue->get_CurrentValue(value.GetAddressOf()));

            ComPtr<IInspectable> propVal;
            RETURN_IF_FAILED(propertyValueFactory->CreateString(value.Get(), propVal.GetAddressOf()));

            boolean replaced;
            RETURN_IF_FAILED(propertySetMap->Insert(key.Get(), propVal.Get(), &replaced));
        }
        return valueSet.CopyTo(valueSetOut);
    }

    HRESULT AdaptiveInputs::ValidateInputs(_In_ IAdaptiveSubmitAction* submitAction, boolean* inputsAreValid)
    {
        boolean allInputsValid = true;

        std::vector<ComPtr<IAdaptiveInputValue>> inputsToValidate;
        GetInputsToValidate(submitAction, inputsToValidate);

        for (auto& inputValue : inputsToValidate)
        {
            boolean currentInputValid;
            RETURN_IF_FAILED(inputValue->Validate(&currentInputValid));

            // If this is the first invalid input, set focus here
            if (allInputsValid && !currentInputValid)
            {
                RETURN_IF_FAILED(inputValue->SetFocus());
            }

            allInputsValid &= currentInputValid;
        }

        *inputsAreValid = allInputsValid;
        return S_OK;
    }

    void AdaptiveInputs::GetInputsToValidate(_In_ IAdaptiveSubmitAction* submitAction,
                                             _Out_ std::vector<ComPtr<IAdaptiveInputValue>>& inputsToValidate)
    {
        ComPtr<IAdaptiveSubmitAction> localSubmitAction(submitAction);
        ComPtr<AdaptiveNamespace::AdaptiveSubmitAction> submitActionImpl =
            PeekInnards<AdaptiveNamespace::AdaptiveSubmitAction>(localSubmitAction);
        InternalId actionId = submitActionImpl->GetInternalId();

        std::size_t card = m_containerCardForAction[actionId.Hash()];
        while (card != InternalId().Hash())
        {
            const auto& inputsInCard = m_inputsPerCard[card];

            for (const auto& inputId : inputsInCard)
            {
                inputsToValidate.emplace_back(m_inputValues[inputId]);
            }

            if (m_parentCard.find(card) != m_parentCard.end())
            {
                card = m_parentCard[card];
            }
            else
            {
                break;
            }
        }
    }

    void AdaptiveInputs::GetAllInputs(_Out_ std::vector<ComPtr<IAdaptiveInputValue>>& inputs)
    {
        for (const auto& input : m_inputValues)
        {
            inputs.emplace_back(input.second);
        }
    }
}
