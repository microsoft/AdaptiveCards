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
                   winrt::xaml::UIElement const& uiInputElement,
                   winrt::xaml_controls::Border const& validationBorder);
        InputValue();

        winrt::IAdaptiveInputElement InputElement() { return m_adaptiveInputElement; };
        winrt::xaml::UIElement ErrorMessage() { return m_validationError; };
        void ErrorMessage(winrt::xaml::UIElement const& errorMessage) { m_validationError = errorMessage; };
        bool Validate();
        void SetFocus();
        void SetAccessibilityProperties(bool isInputValid);

        virtual winrt::hstring CurrentValue() = 0;

    protected:
        virtual bool IsValueValid();
        virtual void SetValidation(bool isValid);

        winrt::IAdaptiveInputElement m_adaptiveInputElement;
        winrt::xaml::UIElement m_uiInputElement;
        winrt::xaml_controls::Border m_validationBorder;
        winrt::xaml::UIElement m_validationError;
    };

    // Base class for AdaptiveTextInput
    struct TextInputBase : public InputValue
    {
    public:
        TextInputBase(winrt::AdaptiveTextInput const& adaptiveTextInput,
                      winrt::xaml::UIElement const& uiTextInputElement,
                      winrt::xaml_controls::Border const& validationBorder);

    protected:
        virtual bool IsValueValid() override;
        winrt::AdaptiveTextInput m_adaptiveTextInput;
    };

    // Input value for Input.Text
    struct TextInputValue : public TextInputBase
    {
    public:
        TextInputValue(winrt::AdaptiveTextInput const& adaptiveTextInput,
                       winrt::xaml_controls::TextBox const& uiTextBoxElement,
                       winrt::xaml_controls::Border const& validationBorder);

    private:
        winrt::hstring CurrentValue() override { return m_textBoxElement.Text(); };
        winrt::xaml_controls::TextBox m_textBoxElement;
    };

    struct PasswordInputValue : public TextInputBase
    {
    public:
        PasswordInputValue(winrt::AdaptiveTextInput const& adaptiveTextInput,
                           winrt::xaml_controls::PasswordBox const& uiPasswordElement,
                           winrt::xaml_controls::Border const& validationBorder);

    private:
        winrt::hstring CurrentValue() override { return m_passwordElement.Password(); };

    protected:
        winrt::xaml_controls::IPasswordBox m_passwordElement;
    };

    // Input value for Input.Number
    class NumberInputValue : public InputValue
    {
    public:
        NumberInputValue(winrt::AdaptiveNumberInput const& adaptiveNumberInput,
                         winrt::xaml_controls::TextBox const& uiInputTextBoxElement,
                         winrt::xaml_controls::Border const& validationBorder);

        winrt::hstring CurrentValue() override { return m_textBoxElement.Text(); };

    private:
        bool IsValueValid();
        winrt::xaml_controls::TextBox m_textBoxElement;
        winrt::AdaptiveNumberInput m_adaptiveNumberInput;
    };

    // Input value for Input.Date
    struct DateInputValue : public InputValue
    {
    public:
        DateInputValue(winrt::AdaptiveDateInput const& adaptiveDateInput,
                       winrt::xaml_controls::CalendarDatePicker const& uiDatePickerElement,
                       winrt::xaml_controls::Border const& validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        winrt::AdaptiveDateInput m_adaptiveDateInput;
        winrt::xaml_controls::CalendarDatePicker m_datePickerElement;
    };

    // Input value for Input.Time
    struct TimeInputValue : public InputValue
    {
    public:
        TimeInputValue(winrt::AdaptiveTimeInput adaptiveTimeInput,
                       winrt::xaml_controls::TimePicker uiTimePickerElement,
                       winrt::xaml_controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveTimeInput m_adaptiveTimeInput;
        winrt::xaml_controls::TimePicker m_timePickerElement;
    };

    // Input value for Input.Toggle
    struct ToggleInputValue : public InputValue
    {
    public:
        ToggleInputValue(winrt::AdaptiveToggleInput adaptiveToggleInput,
                         winrt::xaml_controls::CheckBox uiCheckBoxElement,
                         winrt::xaml_controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveToggleInput m_adaptiveToggleInput;
        winrt::xaml_controls::CheckBox m_checkBoxElement;
    };

    // Input value for Input.ChoiceSet with compact style
    struct CompactChoiceSetInputValue : public InputValue
    {
    public:
        CompactChoiceSetInputValue(winrt::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                   winrt::xaml_controls::Primitives::Selector choiceSetSelector,
                                   winrt::xaml_controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        winrt::xaml_controls::Primitives::Selector m_selectorElement;
        winrt::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with expanded style
    struct ExpandedChoiceSetInputValue : public InputValue
    {
    public:
        ExpandedChoiceSetInputValue(winrt::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                    winrt::xaml_controls::Panel uiChoiceSetElement,
                                    winrt::xaml_controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        void SetFocus();

        winrt::xaml_controls::Panel m_panelElement;
        winrt::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with filtered style
    struct FilteredChoiceSetInputValue : public InputValue
    {
    public:
        FilteredChoiceSetInputValue(winrt::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                    winrt::xaml_controls::AutoSuggestBox uiChoiceSetElement,
                                    winrt::xaml_controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveChoiceInput GetSelectedChoice();

        winrt::xaml_controls::AutoSuggestBox m_autoSuggestBox;
        winrt::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };
}
