#pragma once

#include "json/json.h"
#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class InputItem
    {
    public:
        InputItem(
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputElement* adaptiveInputElement,
            ABI::Windows::UI::Xaml::IUIElement* uiInputElement) :
            m_adaptiveInputElement(adaptiveInputElement),
            m_uiInputElement(uiInputElement)
        {}

        void Serialize(Json::Value& jsonValue);

    private:
        void SerializeChoiceSetInput(Json::Value& jsonValue, const char* idString);
        void SerializeDateInput(Json::Value& jsonValue, const char* idString);
        void SerializeTextInput(Json::Value& jsonValue, const char* idString);
        void SerializeTimeInput(Json::Value& jsonValue, const char* idString);
        void SerializeToggleInput(Json::Value& jsonValue, const char* idString);

        void GetChoiceValue(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex, std::string& choiceValue);

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputElement> m_adaptiveInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiInputElement;
    };
}}