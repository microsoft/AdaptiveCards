// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveInputs.h"
#include "AdaptiveInputs.g.cpp"
#include "AdaptiveRenderArgs.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    winrt::Windows::Data::Json::JsonObject AdaptiveInputs::AsJson()
    {
        return StringToJsonObject(GetInputItemsAsJsonString());
    }

    void AdaptiveInputs::AddInputValue(WinUI3::IAdaptiveInputValue const& inputValue, _In_ WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        auto parentCard = renderArgs.ParentCard();
        auto cardId = parentCard.InternalId();
        auto inputElement = inputValue.InputElement().as<ObjectModel::WinUI3::IAdaptiveInputElement>();
        auto inputElementAsCardElement = inputElement.as<ObjectModel::WinUI3::IAdaptiveCardElement>();
        auto inputId = inputElementAsCardElement.Id();
        auto id = HStringToUTF8(inputId);

        m_inputsPerCard[cardId].push_back(id);
        m_inputValues[id] = inputValue;
    }

    uint32_t AdaptiveInputs::GetInternalIdFromAction(ObjectModel::WinUI3::IAdaptiveActionElement const& action)
    {
        auto actionType = action.ActionType();

        if (actionType == ObjectModel::WinUI3::ActionType::Execute)
        {
            return action.as<ObjectModel::WinUI3::AdaptiveExecuteAction>().InternalId();
        }
        else if (actionType == ObjectModel::WinUI3::ActionType::Submit)
        {
            return action.as<ObjectModel::WinUI3::AdaptiveSubmitAction>().InternalId();
        }
        else
        {
            return 0;
        }
    }

    void AdaptiveInputs::LinkSubmitActionToCard(ObjectModel::WinUI3::IAdaptiveActionElement const& action,
                                                WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        uint32_t actionId = GetInternalIdFromAction(action);
        uint32_t cardId = renderArgs.ParentCard().InternalId();
        m_containerCardForAction[actionId] = cardId;
    }

    void AdaptiveInputs::LinkCardToParent(uint32_t cardId, uint32_t parentCardId)
    {
        m_parentCard[cardId] = parentCardId;
    }

    WinUI3::IAdaptiveInputValue AdaptiveInputs::GetInputValue(ObjectModel::WinUI3::IAdaptiveInputElement const& inputElement)
    {
        hstring elementId = inputElement.as<ObjectModel::WinUI3::IAdaptiveCardElement>().Id();
        return m_inputValues[HStringToUTF8(elementId)];
    }

    std::string AdaptiveInputs::GetInputItemsAsJsonString()
    {
        Json::Value jsonValue;

        for (auto& inputValue : m_lastRetrievedValues)
        {
            auto cardElement = inputValue.InputElement().as<ObjectModel::WinUI3::IAdaptiveCardElement>();
            std::string key = HStringToUTF8(cardElement.Id());
            jsonValue[key] = HStringToUTF8(inputValue.CurrentValue());
        }

        Json::StreamWriterBuilder writerBuilder;
        std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
        std::ostringstream outStream;
        writer->write(jsonValue, &outStream);
        return outStream.str();
    }

    winrt::Windows::Foundation::Collections::ValueSet AdaptiveInputs::AsValueSet()
    {
        winrt::Windows::Foundation::Collections::ValueSet valueSet;
        auto propertySetMap =
            valueSet.as<winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::IInspectable>>();

        for (auto&& inputValue : m_lastRetrievedValues)
        {
            auto cardElement = inputValue.InputElement().as<ObjectModel::WinUI3::IAdaptiveCardElement>();
            propertySetMap.Insert(cardElement.Id(), winrt::box_value(inputValue.CurrentValue()));
        }

        return valueSet;
    }

    bool AdaptiveInputs::ValidateInputs(ObjectModel::WinUI3::IAdaptiveActionElement const& submitAction)
    {
        bool allInputsValid = true;
        auto inputsToValidate = GetInputsToValidate(submitAction);

        for (auto& inputValue : inputsToValidate)
        {
            bool currentInputValid = inputValue.Validate();

            // If this is the first invalid input, set focus here
            if (allInputsValid && !currentInputValid)
            {
                inputValue.SetFocus();
            }

            allInputsValid &= currentInputValid;
        }

        // If validation succeeded, then cache the validated inputs
        if (allInputsValid)
        {
            m_lastRetrievedValues = std::move(inputsToValidate);
        }
        else
        {
            m_lastRetrievedValues.clear();
        }

        return allInputsValid;
    }

    std::vector<WinUI3::IAdaptiveInputValue> AdaptiveInputs::GetInputsToValidate(ObjectModel::WinUI3::IAdaptiveActionElement const& action)
    {
        std::vector<WinUI3::IAdaptiveInputValue> inputsToValidate;

        uint32_t actionId = GetInternalIdFromAction(action);
        std::size_t card = m_containerCardForAction[actionId];
        // TODO: This is equivalent to "is the card id 0" - InternalId() inits to zero, Hash returns that
        while (card != ::AdaptiveCards::InternalId().Hash())
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

        return inputsToValidate;
    }
}
