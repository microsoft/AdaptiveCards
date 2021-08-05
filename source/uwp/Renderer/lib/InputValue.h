// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards::Rendering::Uwp
{
    // Base class for input values. The InputValue is responsible for getting the current value and submit time, and also handles input validation.
    class DECLSPEC_UUID("BB1D1269-2243-4F34-B4EC-5216296EBBA0") InputValue
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue>
    {
    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInputElement,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* uiInputElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_InputElement(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement** inputElement);
        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) = 0;
        IFACEMETHODIMP get_ErrorMessage(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** uiErrorMessage);
        IFACEMETHODIMP put_ErrorMessage(_In_ ABI::Windows::UI::Xaml::IUIElement* uiErrorMessage);

        IFACEMETHODIMP Validate(_Out_ boolean* isInputValid);
        IFACEMETHODIMP SetFocus();
        IFACEMETHODIMP SetAccessibilityProperties(boolean isInputValid);

    protected:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid);
        virtual HRESULT SetValidation(boolean isValid);

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement> m_adaptiveInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiInputElement;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IBorder> m_validationBorder;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_validationError;
    };

    // Base class for input value types that use ITextBox (Input.Text and Input.Number)
    class TextInputBase : public InputValue
    {
    public:
        TextInputBase() {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInputElement* adaptiveInputElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* uiTextBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    protected:
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ITextBox> m_textBoxElement;
    };

    // Input value for Input.Text
    class TextInputValue : public TextInputBase
    {
    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextInput* adaptiveTextInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* uiTextBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

    private:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextInput> m_adaptiveTextInput;
    };

    // Input value for Input.Number
    class NumberInputValue : public TextInputBase
    {
    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveNumberInput* adaptiveNumberInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* uiTextBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

    private:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveNumberInput> m_adaptiveNumberInput;
    };

    // Input value for Input.Date
    class DateInputValue : public InputValue
    {
    public:
        DateInputValue() {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveDateInput* adaptiveDateInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ICalendarDatePicker* uiDatePickerElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveDateInput> m_adaptiveDateInput;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ICalendarDatePicker> m_datePickerElement;
    };

    // Input value for Input.Time
    class TimeInputValue : public InputValue
    {
    public:
        TimeInputValue() {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTimeInput* adaptiveTimeInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITimePicker* uiTimePickerElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    private:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTimeInput> m_adaptiveTimeInput;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ITimePicker> m_timePickerElement;
    };

    // Input value for Input.Toggle
    class ToggleInputValue : public InputValue
    {
    public:
        ToggleInputValue() {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveToggleInput* adaptiveTimeInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ICheckBox* uiCheckBoxElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    private:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveToggleInput> m_adaptiveToggleInput;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::ICheckBox> m_checkBoxElement;
    };

    // Input value for Input.ChoiceSet with compact style
    class CompactChoiceSetInputValue : public InputValue
    {
    public:
        CompactChoiceSetInputValue() {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::Primitives::ISelector* choiceSetSelector,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::Primitives::ISelector> m_selectorElement;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceSetInput> m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with expanded style
    class ExpandedChoiceSetInputValue : public InputValue
    {
    public:
        ExpandedChoiceSetInputValue() {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IPanel* uiChoiceSetElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    private:
        IFACEMETHODIMP SetFocus() override;

        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IPanel> m_panelElement;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceSetInput> m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with filtered style
    class FilteredChoiceSetInputValue : public InputValue
    {
    public:
        FilteredChoiceSetInputValue() {}

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IAutoSuggestBox* uiChoiceSetElement,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IBorder* validationBorder);

        IFACEMETHODIMP get_CurrentValue(_Outptr_ HSTRING* serializedUserInput) override;

    private:
        virtual HRESULT IsValueValid(_Out_ boolean* isInputValid) override;

        HRESULT GetSelectedChoice(ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceInput** adaptiveChoiceInput);

        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IAutoSuggestBox> m_autoSuggestBox;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceSetInput> m_adaptiveChoiceSetInput;
    };
}
