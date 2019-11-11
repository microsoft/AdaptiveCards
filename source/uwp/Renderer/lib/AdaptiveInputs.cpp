// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveInputs.h"

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
    AdaptiveInputs::AdaptiveInputs() { m_inputValues = std::make_shared<std::vector<ComPtr<IAdaptiveInputValue>>>(); }

    HRESULT AdaptiveInputs::RuntimeClassInitialize() noexcept
    {
        m_inputValues = std::make_shared<std::vector<ComPtr<IAdaptiveInputValue>>>();
        return S_OK;
    }

    HRESULT AdaptiveInputs::AsJson(_COM_Outptr_ IJsonObject** value)
    {
        return StringToJsonObject(GetInputItemsAsJsonString(), value);
    }

    HRESULT AdaptiveInputs::AddInputValue(_In_ IAdaptiveInputValue* inputValue)
    {
        m_inputValues->push_back(inputValue);
        return S_OK;
    }

    std::string AdaptiveInputs::GetInputItemsAsJsonString()
    {
        Json::Value jsonValue;
        for (auto& inputValue : *m_inputValues)
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

        for (auto& inputValue : *m_inputValues)
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

    HRESULT AdaptiveInputs::ValidateInputs(boolean* inputsAreValid)
    {
        boolean allInputsValid = true;
        for (auto& inputValue : *m_inputValues)
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
}
