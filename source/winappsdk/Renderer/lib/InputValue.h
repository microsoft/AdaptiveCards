// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "winrt/AdaptiveCards.Rendering.WinUI3.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3
{
    // Base class for input values. The InputValue is responsible for getting the current value and submit time, and also handles input validation.
    struct DECLSPEC_UUID("BB1D1269-2243-4F34-B4EC-5216296EBBA0") InputValue : public winrt::implements<InputValue, IAdaptiveInputValue>
    {
    public:
        InputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement const& adaptiveInputElement,
                   winrt::Windows::UI::Xaml::UIElement const& uiInputElement,
                   winrt::Windows::UI::Xaml::Controls::Border const& validationBorder);
        InputValue();

        // TODO: getting compile errors with this for some reason...
        //property<winrt::Windows::UI::Xaml::UIElement> ErrorMessage;
        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement InputElement()
        {
            return m_adaptiveInputElement;
        };
       winrt::Windows::UI::Xaml::UIElement ErrorMessage() { return m_validationError; };
        void ErrorMessage(winrt::Windows::UI::Xaml::UIElement const& errorMessage)
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

        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement m_adaptiveInputElement;
        winrt::Windows::UI::Xaml::UIElement m_uiInputElement;
        winrt::Windows::UI::Xaml::Controls::Border m_validationBorder;
        winrt::Windows::UI::Xaml::UIElement m_validationError;
    };

    // Base class for AdaptiveTextInput
    struct TextInputBase : public InputValue
    {
    public:
        TextInputBase(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput const& adaptiveTextInput,
                      winrt::Windows::UI::Xaml::UIElement const& uiTextInputElement,
                      winrt::Windows::UI::Xaml::Controls::Border const& validationBorder);

    protected:
        virtual bool IsValueValid() override;
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput m_adaptiveTextInput;
    };

    // Input value for Input.Text
    struct TextInputValue : public TextInputBase
    {
    public:
        TextInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput const& adaptiveTextInput,
                       winrt::Windows::UI::Xaml::Controls::TextBox const& uiTextBoxElement,
                       winrt::Windows::UI::Xaml::Controls::Border const& validationBorder);

    private:
        winrt::hstring CurrentValue() override { return m_textBoxElement.Text(); };
        winrt::Windows::UI::Xaml::Controls::TextBox m_textBoxElement;
    };

    struct PasswordInputValue : public TextInputBase
    {
    public:
        PasswordInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput const& adaptiveTextInput,
                           winrt::Windows::UI::Xaml::Controls::PasswordBox const& uiPasswordElement,
                           winrt::Windows::UI::Xaml::Controls::Border const& validationBorder);

    private:
        winrt::hstring CurrentValue() override { return m_passwordElement.Password(); };

    protected:
        winrt::Windows::UI::Xaml::Controls::IPasswordBox m_passwordElement;
    };

    // Input value for Input.Number
    class NumberInputValue : public InputValue
    {
    public:
        NumberInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveNumberInput const& adaptiveNumberInput,
                         winrt::Windows::UI::Xaml::Controls::TextBox const& uiInputTextBoxElement,
                         winrt::Windows::UI::Xaml::Controls::Border const& validationBorder);

        winrt::hstring CurrentValue() override { return m_textBoxElement.Text(); };

    private:
        bool IsValueValid();
        winrt::Windows::UI::Xaml::Controls::TextBox m_textBoxElement;
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveNumberInput m_adaptiveNumberInput;
    };

    // Input value for Input.Date
    struct DateInputValue : public InputValue
    {
    public:
        DateInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveDateInput const& adaptiveDateInput,
                       winrt::Windows::UI::Xaml::Controls::CalendarDatePicker const& uiDatePickerElement,
                       winrt::Windows::UI::Xaml::Controls::Border const& validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveDateInput m_adaptiveDateInput;
        winrt::Windows::UI::Xaml::Controls::CalendarDatePicker m_datePickerElement;
    };

    // Input value for Input.Time
    struct TimeInputValue : public InputValue
    {
    public:
        TimeInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTimeInput adaptiveTimeInput,
                       winrt::Windows::UI::Xaml::Controls::TimePicker uiTimePickerElement,
                       winrt::Windows::UI::Xaml::Controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveTimeInput m_adaptiveTimeInput;
        winrt::Windows::UI::Xaml::Controls::TimePicker m_timePickerElement;
    };

    // Input value for Input.Toggle
    struct ToggleInputValue : public InputValue
    {
    public:
        ToggleInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveToggleInput adaptiveToggleInput,
                         winrt::Windows::UI::Xaml::Controls::CheckBox uiCheckBoxElement,
                         winrt::Windows::UI::Xaml::Controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveToggleInput m_adaptiveToggleInput;
        winrt::Windows::UI::Xaml::Controls::CheckBox m_checkBoxElement;
    };

    // Input value for Input.ChoiceSet with compact style
    struct CompactChoiceSetInputValue : public InputValue
    {
    public:
        CompactChoiceSetInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                   winrt::Windows::UI::Xaml::Controls::Primitives::Selector choiceSetSelector,
                                   winrt::Windows::UI::Xaml::Controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        winrt::Windows::UI::Xaml::Controls::Primitives::Selector m_selectorElement;
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with expanded style
    struct ExpandedChoiceSetInputValue : public InputValue
    {
    public:
        ExpandedChoiceSetInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                    winrt::Windows::UI::Xaml::Controls::Panel uiChoiceSetElement,
                                    winrt::Windows::UI::Xaml::Controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        void SetFocus();

        winrt::Windows::UI::Xaml::Controls::Panel m_panelElement;
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };

    // Input value for Input.ChoiceSet with filtered style
    struct FilteredChoiceSetInputValue : public InputValue
    {
    public:
        FilteredChoiceSetInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                    winrt::Windows::UI::Xaml::Controls::AutoSuggestBox uiChoiceSetElement,
                                    winrt::Windows::UI::Xaml::Controls::Border validationBorder);

        winrt::hstring CurrentValue() override;

    private:
        bool IsValueValid();

        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceInput GetSelectedChoice();

        winrt::Windows::UI::Xaml::Controls::AutoSuggestBox m_autoSuggestBox;
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput m_adaptiveChoiceSetInput;
    };
}
