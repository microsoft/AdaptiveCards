#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class DECLSPEC_UUID("BB1D1269-2243-4F34-B4EC-5216296EBBA0") InputValue :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue>
    {
    public:

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputElement* adaptiveInputElement,
            ABI::Windows::UI::Xaml::IUIElement* uiInputElement)
        {
            m_adaptiveInputElement = adaptiveInputElement;
            m_uiInputElement = uiInputElement;
            return S_OK;
        }

        IFACEMETHODIMP get_InputElement(_Out_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputElement** inputElement);
        IFACEMETHODIMP get_CurrentValue(_Out_ HSTRING * serializedUserInput);

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