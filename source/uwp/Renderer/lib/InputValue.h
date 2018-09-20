#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("BB1D1269-2243-4F34-B4EC-5216296EBBA0") InputValue :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveInputValue>
    {
    public:

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveNamespace::IAdaptiveInputElement* adaptiveInputElement,
            ABI::Windows::UI::Xaml::IUIElement* uiInputElement)
        {
            m_adaptiveInputElement = adaptiveInputElement;
            m_uiInputElement = uiInputElement;
            return S_OK;
        }

        IFACEMETHODIMP get_InputElement(_Out_ ABI::AdaptiveNamespace::IAdaptiveInputElement** inputElement);
        IFACEMETHODIMP get_CurrentValue(_Out_ HSTRING * serializedUserInput);

    private:
        std::string SerializeChoiceSetInput() const;
        std::string SerializeDateInput() const;
        std::string SerializeTextInput() const;
        std::string SerializeTimeInput() const;
        std::string SerializeToggleInput() const;

        std::string GetChoiceValue(ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex) const;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveInputElement> m_adaptiveInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiInputElement;
    };
AdaptiveNamespaceEnd