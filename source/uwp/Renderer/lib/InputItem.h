#pragma once

#include "json/json.h"
#include "AdaptiveCards.Uwp.h"

namespace AdaptiveCards { namespace Uwp
{
    class InputItem
    {
    public:
        InputItem(
            ABI::AdaptiveCards::Uwp::IAdaptiveInputElement* adaptiveInputElement,
            ABI::Windows::UI::Xaml::IUIElement* uiInputElement) :
            m_adaptiveInputElement(adaptiveInputElement),
            m_uiInputElement(uiInputElement)
        {}

        void Serialize(Json::Value& jsonValue) const;

    private:
        void SerializeChoiceSetInput(Json::Value& jsonValue, const char* idString) const;
        void SerializeDateInput(Json::Value& jsonValue, const char* idString) const;
        void SerializeTextInput(Json::Value& jsonValue, const char* idString) const;
        void SerializeTimeInput(Json::Value& jsonValue, const char* idString) const;
        void SerializeToggleInput(Json::Value& jsonValue, const char* idString) const;

        void GetChoiceValue(ABI::AdaptiveCards::Uwp::IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex, std::string& choiceValue) const;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveInputElement> m_adaptiveInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiInputElement;
    };
}}