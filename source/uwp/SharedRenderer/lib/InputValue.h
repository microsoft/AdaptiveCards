// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering
{
    // Base class for input values. The InputValue is responsible for getting the current value and submit time, and also handles input validation.
    struct DECLSPEC_UUID("BB1D1269-2243-4F34-B4EC-5216296EBBA0") InputValue : public winrt::implements<InputValue, IAdaptiveInputValue>
    {
    public:
        InputValue(winrt::IAdaptiveInputElement const& adaptiveInputElement,
                   winrt::UIElement const& uiInputElement,
                   winrt::Border const& validationBorder);
        InputValue();

        winrt::IAdaptiveInputElement InputElement() { return m_adaptiveInputElement; };
        winrt::UIElement ErrorMessage() { return m_validationError; };
        void ErrorMessage(winrt::UIElement const& errorMessage)
        {
            m_validationError = errorMessage;
        };
        bool Validate();
        void SetFocus();
        void SetAccessibilityProperties(bool isInputValid);

        virtual winrt::hstring CurrentValue() = 0;

    protected:
        virtual bool IsValueValid();
        virtual void SetValidation(bool isValid);

        winrt::IAdaptiveInputElement m_adaptiveInputElement;
        winrt::UIElement m_uiInputElement;
        winrt::Border m_validationBorder;
        winrt::UIElement m_validationError;
    };

    // Base class for AdaptiveTextInput
    struct TextInputBase : public InputValue
    {
    public:
        TextInputBase(winrt::AdaptiveTextInput const& adaptiveTextInput,
                      winrt::UIElement const& uiTextInputElement,
                      winrt::Border const& validationBorder);

    protected:
        virtual bool IsValueValid() override;
        winrt::AdaptiveTextInput m_adaptiveTextInput;
    };

    // Input value for Input.Text
    struct TextInputValue : public TextInputBase
    {
    public:
        TextInputValue(winrt::AdaptiveTextInput const& adaptiveTextInput,
                       winrt::TextBox const& uiTextBoxElement,
                       winrt::Border const& validationBorder);

    private:
        winrt::hstring CurrentValue() override { return m_textBoxElement.Text(); };
        winrt::TextBox m_textBoxElement;
    };

    struct PasswordInputValue : public TextInputBase
    {
    public:
        PasswordInputValue(winrt::AdaptiveTextInput const& adaptiveTextInput,
                           winrt::PasswordBox const& uiPasswordElement,
                           winrt::Border const& validationBorder);

    private:
        winrt::hstring CurrentValue() override { return m_passwordElement.Password(); };

    protected:
        winrt::IPasswordBox m_passwordElement;
    };

    // Input value for Input.Number
    class NumberInputValue : public InputValue
    {
    public:
        NumberInputValue(winrt::AdaptiveNumberInput const& adaptiveNumberInput,
                         winrt::TextBox const& uiInputTextBoxElement,
                         winrt::Border const& validationBorder);

        winrt::hstring CurrentValue() override { return m_textBoxElement.Text(); };

    private:
        bool IsValueValid();
        winrt::TextBox m_textBoxElement;
        winrt::AdaptiveNumberInput m_adaptiveNumberInput;
    };

    // Input value for Input.Date
    struct DateInputValue : public InputValue
    {
    public:
        DateInputValue(winrt::AdaptiveDateInput const& adaptiveDateInput,
                       winrt::CalendarDatePicker const& uiDatePickerElement,
                       winrt::Border const& validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        winrt::AdaptiveDateInput m_adaptiveDateInput;
        winrt::CalendarDatePicker m_datePickerElement;
    };

    // Input value for Input.Time
    struct TimeInputValue : public InputValue
    {
    public:
        TimeInputValue(winrt::AdaptiveTimeInput adaptiveTimeInput, winrt::TimePicker uiTimePickerElement, winrt::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveTimeInput m_adaptiveTimeInput;
        winrt::TimePicker m_timePickerElement;
    };

    // Input value for Input.Toggle
    struct ToggleInputValue : public InputValue
    {
    public:
        ToggleInputValue(winrt::AdaptiveToggleInput adaptiveToggleInput, winrt::CheckBox uiCheckBoxElement, winrt::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveToggleInput m_adaptiveToggleInput;
        winrt::CheckBox m_checkBoxElement;
    };

    // Input value for Input.ChoiceSet with compact style
    struct CompactChoiceSetInputValue : public InputValue
    {
    public:
        CompactChoiceSetInputValue(winrt::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                   winrt::Selector choiceSetSelector,
                                   winrt::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        winrt::Selector m_selectorElement;
        winrt::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with expanded style
    struct ExpandedChoiceSetInputValue : public InputValue
    {
    public:
        ExpandedChoiceSetInputValue(winrt::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                    winrt::Panel uiChoiceSetElement,
                                    winrt::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        void SetFocus();

        winrt::Panel m_panelElement;
        winrt::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with filtered style
    struct FilteredChoiceSetInputValue : public InputValue
    {
    public:
        FilteredChoiceSetInputValue(winrt::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                    winrt::AutoSuggestBox uiChoiceSetElement,
                                    winrt::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveChoiceInput GetSelectedChoice();

        winrt::AutoSuggestBox m_autoSuggestBox;
        winrt::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };
}
