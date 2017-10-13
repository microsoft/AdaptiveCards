#pragma once

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

        std::string Serialize() const;
        std::string GetIdString() const;
        HSTRING GetId() const;


    private:
        std::string SerializeChoiceSetInput(const char* idString) const;
        std::string SerializeDateInput(const char* idString) const;
        std::string SerializeTextInput(const char* idString) const;
        std::string SerializeTimeInput(const char* idString) const;
        std::string SerializeToggleInput(const char* idString) const;

        std::string GetChoiceValue(ABI::AdaptiveCards::Uwp::IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex) const;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveInputElement> m_adaptiveInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiInputElement;
    };
}}