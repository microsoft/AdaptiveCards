#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class InputItem
    {
    public:
        InputItem(
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputElement* adaptiveInputElement,
            ABI::Windows::UI::Xaml::IUIElement* uiInputElement) :
            m_adaptiveInputElement(adaptiveInputElement),
            m_uiInputElement(uiInputElement)
        {}

        std::string Serialize() const;
        std::string GetIdString() const;
        HSTRING GetId() const;


    private:
        std::string SerializeChoiceSetInput() const;
        std::string SerializeDateInput() const;
        std::string SerializeTextInput() const;
        std::string SerializeTimeInput() const;
        std::string SerializeToggleInput() const;

        std::string GetChoiceValue(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex) const;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputElement> m_adaptiveInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiInputElement;
    };
}}}