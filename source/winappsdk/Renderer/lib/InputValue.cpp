// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "InputValue.h"
#include "json/json.h"
#include "XamlHelpers.h"
#include <windows.globalization.datetimeformatting.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Globalization::DateTimeFormatting;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Documents;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace AdaptiveCards::Rendering::WinUI3;

namespace winrt::AdaptiveCards::Rendering::WinUI3
{
    /*   HRESULT ValidateIfNeeded(IAdaptiveInputValue* inputValue)
       {
           HString currentValue;
           RETURN_IF_FAILED(inputValue->get_CurrentValue(currentValue.GetAddressOf()));

           return inputValue->Validate(nullptr);
       }*/

    // TODO: what is this function?
    void ValidateIfNeeded(rtrender::IAdaptiveInputValue const& inputValue)
    {
        auto currentValue = inputValue.CurrentValue();

        inputValue.Validate();
    }

    // HRESULT InputValue::RuntimeClassInitialize(_In_ IAdaptiveInputElement* adaptiveInputElement,
    //                                           _In_ IUIElement* uiInputElement,
    //                                           _In_ IBorder* validationBorder)
    //{
    //    m_adaptiveInputElement = adaptiveInputElement;
    //    m_uiInputElement = uiInputElement;
    //    m_validationBorder = validationBorder;
    //
    //    return S_OK;
    //}

    InputValue::InputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement const& adaptiveInputElement,
                           winrt::Windows::UI::Xaml::UIElement const& uiInputElement,
                           winrt::Windows::UI::Xaml::Controls::Border const& validationBorder) :
        m_adaptiveInputElement(adaptiveInputElement),
        m_uiInputElement(uiInputElement), m_validationBorder(validationBorder), m_validationError(nullptr)

        // TODO: Figure out how to fix: no default constructor exists for rtxaml::UIElement
    {
        auto k = 5;
    }

    InputValue::InputValue() :  m_uiInputElement(nullptr), m_validationError(nullptr){};

    // HRESULT InputValue::Validate(_Out_ boolean* isInputValid)
    //{
    //    boolean isValid;
    //    RETURN_IF_FAILED(IsValueValid(&isValid));
    //
    //    RETURN_IF_FAILED(SetValidation(isValid));
    //
    //    if (isInputValid)
    //    {
    //        *isInputValid = isValid;
    //    }
    //
    //    return S_OK;
    //}

    bool InputValue::Validate()
    {
        /*boolean isValid;
        RETURN_IF_FAILED(IsValueValid(&isValid));*/
        auto isValid = IsValueValid();

        // RETURN_IF_FAILED(SetValidation(isValid));
        SetValidation(isValid);

        return isValid;
    }

    void InputValue::SetFocus()
    {
        // Set focus on the input control
        /* ComPtr<IControl> inputAsControl;
         RETURN_IF_FAILED(m_uiInputElement.As(&inputAsControl));

         boolean isFocused;
         RETURN_IF_FAILED(inputAsControl->Focus(FocusState_Programmatic, &isFocused));

         return S_OK;*/
        if (const auto inputAsControl = m_uiInputElement.try_as<rtxaml::Controls::Control>())
        {
            inputAsControl.Focus(rtxaml::FocusState::Programmatic);
        }
    }

    void InputValue::SetAccessibilityProperties(bool isInputValid)
    {
        /*ComPtr<IAutomationPropertiesStatics5> automationPropertiesStatics;

        RETURN_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationPropertiesStatics));*/

        rtxaml::Automation::IAutomationPropertiesStatics5 automationPropertiesStatics{};

        // This smart pointer is created as the variable inputUIElementParentContainer may contain the border instead of the
        // actual element if validations are required. If these properties are set into the border then they are not mentioned.
        /*ComPtr<IUIElement> uiInputElement(m_uiInputElement);

        ComPtr<IDependencyObject> inputUIElementAsDependencyObject;
        RETURN_IF_FAILED(uiInputElement.As(&inputUIElementAsDependencyObject));

        ComPtr<IVector<DependencyObject*>> uiElementDescribers;
        RETURN_IF_FAILED(automationPropertiesStatics->GetDescribedBy(inputUIElementAsDependencyObject.Get(),
                                                                     uiElementDescribers.GetAddressOf()));

        ComPtr<IUIElement> uiValidationError(m_validationError);
        ComPtr<IDependencyObject> uiValidationErrorAsDependencyObject;
        RETURN_IF_FAILED(uiValidationError.As(&uiValidationErrorAsDependencyObject));*/
        auto inputUIElementAsDependencyObject = m_uiInputElement.as<rtxaml::DependencyObject>();

        auto uiElementDescribers = automationPropertiesStatics.GetDescribedBy(inputUIElementAsDependencyObject);

        auto uiValidationErrorAsDependencyObject = m_validationError.as<rtxaml::DependencyObject>();

        uint32_t index;
        bool found = uiElementDescribers.IndexOf(uiValidationErrorAsDependencyObject, index);
        // RETURN_IF_FAILED(uiElementDescribers->IndexOf(uiValidationErrorAsDependencyObject.Get(), &index, &found));

        // If the error message is visible then the input element must be described by it, otherwise we try to remove it from the list of describers
        if (!isInputValid && !found)
        {
            /* RETURN_IF_FAILED(uiElementDescribers->Append(uiValidationErrorAsDependencyObject.Get()));*/
            uiElementDescribers.Append(uiValidationErrorAsDependencyObject);
        }
        else if (isInputValid && found)
        {
            /* RETURN_IF_FAILED(uiElementDescribers->RemoveAt(index));*/
            uiElementDescribers.RemoveAt(index);
        }

        /* RETURN_IF_FAILED(automationPropertiesStatics->SetIsDataValidForForm(inputUIElementAsDependencyObject.Get(), isInputValid));*/
        automationPropertiesStatics.SetIsDataValidForForm(inputUIElementAsDependencyObject, isInputValid);
    }

    /*HRESULT InputValue::get_ErrorMessage(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** uiErrorMessage)
    {
        return m_validationError.CopyTo(uiErrorMessage);
    }*/

    /*HRESULT InputValue::put_ErrorMessage(_In_ IUIElement* uiErrorMessage)
    {
        m_validationError = uiErrorMessage;
        return S_OK;
    }*/

    bool InputValue::IsValueValid()
    {
        /*boolean isRequired;
        RETURN_IF_FAILED(m_adaptiveInputElement->get_IsRequired(&isRequired));*/
        auto isRequired = m_adaptiveInputElement.IsRequired();

        bool isRequiredValid = true;
        if (isRequired)
        {
            /*HString currentValue;
            RETURN_IF_FAILED(get_CurrentValue(currentValue.GetAddressOf()));*/
            auto currentValue = CurrentValue();

            isRequiredValid = !currentValue.empty();
        }

        /* *isInputValid = isRequiredValid;*/
        return isRequiredValid;
    }

    void InputValue::SetValidation(bool isInputValid)
    {
        // Show or hide the border
        if (m_validationBorder)
        {
            if (isInputValid)
            {
                m_validationBorder.BorderThickness({0, 0, 0, 0});
            }
            else
            {
                m_validationBorder.BorderThickness({1, 1, 1, 1});
            }
        }

        // Show or hide the error message
        if (m_validationError)
        {
            if (isInputValid)
            {
                m_validationError.Visibility(rtxaml::Visibility::Collapsed);
            }
            else
            {
                m_validationError.Visibility(rtxaml::Visibility::Visible);
            }

            /* RETURN_IF_FAILED(SetAccessibilityProperties(isInputValid));*/
            SetAccessibilityProperties(isInputValid);
        }
    }

    /*   HRESULT InputValue::get_InputElement(_COM_Outptr_ IAdaptiveInputElement** inputElement)
       {
           return m_adaptiveInputElement.CopyTo(inputElement);
       }*/

    /*  HRESULT TextInputBase::RuntimeClassInitialize(_In_ IAdaptiveTextInput* adaptiveTextInput,
                                                    _In_ IUIElement* uiTextBoxElement,
                                                    _In_ IBorder* validationBorder)
      {
          m_adaptiveTextInput = adaptiveTextInput;

          Microsoft::WRL::ComPtr<IAdaptiveInputElement> textInputAsAdaptiveInput;
          RETURN_IF_FAILED(m_adaptiveTextInput.As(&textInputAsAdaptiveInput));

          return InputValue::RuntimeClassInitialize(textInputAsAdaptiveInput.Get(), uiTextBoxElement, validationBorder);
      }*/

    TextInputBase::TextInputBase(rtom::AdaptiveTextInput const& adaptiveTextInput,
                                 rtxaml::UIElement const& uiTextInputElement,
                                 rtxaml::Controls::Border const& validationBorder) :
        // TODO: is this the proper way for calling base ctor? Do I need to cast the first argument?
        InputValue(adaptiveTextInput, uiTextInputElement, validationBorder),
        m_adaptiveTextInput(adaptiveTextInput)
    {
    }

    bool TextInputBase::IsValueValid()
    {
        // Call the base class to validate isRequired
        /*boolean isBaseValid;
        RETURN_IF_FAILED(InputValue::IsValueValid(&isBaseValid));*/
        auto isBaseValid = InputValue::IsValueValid();

        // Validate the regex if one exists
        /*HString regex;
        RETURN_IF_FAILED(m_adaptiveTextInput->get_Regex(regex.GetAddressOf()));*/
        auto regex = m_adaptiveTextInput.Regex();

        /*HString currentValue;
        RETURN_IF_FAILED(get_CurrentValue(currentValue.GetAddressOf()));*/
        auto currentValue = CurrentValue();

        bool isRegexValid = true;
        if (!regex.empty() && !currentValue.empty())
        {
            std::string stringPattern = HStringToUTF8(regex);
            std::regex pattern(stringPattern);

            std::string currentValueStdString = HStringToUTF8(currentValue);

            std::smatch matches;
            isRegexValid = std::regex_match(currentValueStdString, matches, pattern);
        }

        return isBaseValid && isRegexValid;
    }

    /*HRESULT TextInputValue::RuntimeClassInitialize(_In_ IAdaptiveTextInput* adaptiveTextInput,
                                                   _In_ ITextBox* uiTextBoxElement,
                                                   _In_ IBorder* validationBorder)
    {
        m_textBoxElement = uiTextBoxElement;

        ComPtr<IUIElement> textBoxAsUIElement;
        RETURN_IF_FAILED(m_textBoxElement.As(&textBoxAsUIElement));

        RETURN_IF_FAILED(TextInputBase::RuntimeClassInitialize(adaptiveTextInput, textBoxAsUIElement.Get(), validationBorder));

        return S_OK;
    }*/

    TextInputValue::TextInputValue(rtom::AdaptiveTextInput const& adaptiveTextInput,
                                   rtxaml::Controls::TextBox const& uiTextBoxElement,
                                   rtxaml::Controls::Border const& validationBorder) :
        TextInputBase(adaptiveTextInput, uiTextBoxElement, validationBorder),
        m_textBoxElement(uiTextBoxElement)
    {
    }

    /*  HRESULT TextInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
      {
          return m_textBoxElement->get_Text(serializedUserInput);
      }*/

  /*  HRESULT PasswordInputValue::RuntimeClassInitialize(_In_ IAdaptiveTextInput* adaptiveTextInput]
                                                       _In_ IPasswordBox* uiPasswordElement,
                                                       _In_ IBorder* validationBorder)
    {
        m_passwordElement = uiPasswordElement;

        ComPtr<IUIElement> passwordAsUIElement;
        RETURN_IF_FAILED(m_passwordElement.As(&passwordAsUIElement));

        RETURN_IF_FAILED(TextInputBase::RuntimeClassInitialize(adaptiveTextInput, passwordAsUIElement.Get(), validationBorder));

        return S_OK;
    }*/

    PasswordInputValue::PasswordInputValue(rtom::AdaptiveTextInput const& adaptiveTextInput,
                                           rtxaml::Controls::PasswordBox const& uiPasswordElement,
                                           rtxaml::Controls::Border const& validationBorder)  // TODO: this is kinda madness? HOW TO AVOID THIS?
    // TODO: is this the right way? Do we need to chain call constructors?
    {
        m_passwordElement = uiPasswordElement;
        // TODO: This is done so we can call TextInputBase "constructor" directly. Can we do it better?
        TextInputBase::Initialize(adaptiveTextInput, uiPasswordElement, validationBorder);
    }

    /*  IFACEMETHODIMP AdaptiveCards::Rendering::WinUI3::PasswordInputValue::CurrentValue()
      {
          return m_passwordElement->get_Password(serializedUserInput);
      }*/

    /*HRESULT NumberInputValue::RuntimeClassInitialize(_In_ IAdaptiveNumberInput* adaptiveNumberInput,
                                                     _In_ ITextBox* uiTextBoxElement,
                                                     _In_ IBorder* validationBorder)
    {
        m_adaptiveNumberInput = adaptiveNumberInput;
        m_textBoxElement = uiTextBoxElement;

        ComPtr<IAdaptiveInputElement> numberInputAsAdaptiveInput;
        RETURN_IF_FAILED(m_adaptiveNumberInput.As(&numberInputAsAdaptiveInput));

        ComPtr<IUIElement> textBoxAsUIElement;
        RETURN_IF_FAILED(m_textBoxElement.As(&textBoxAsUIElement));

        RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(numberInputAsAdaptiveInput.Get(), textBoxAsUIElement.Get(),
    validationBorder)); return S_OK;
    }*/

    NumberInputValue::NumberInputValue(rtom::AdaptiveNumberInput const& adaptiveNumberInput,
                                       rtxaml::Controls::TextBox const& uiInputTextBoxElement,
                                       rtxaml::Controls::Border const& validationBorder) :
        InputValue(adaptiveNumberInput, uiInputTextBoxElement, validationBorder),
        m_adaptiveNumberInput(adaptiveNumberInput), m_textBoxElement(uiInputTextBoxElement)
    {
    }

    // HRESULT NumberInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
    //{
    //    return m_textBoxElement->get_Text(serializedUserInput);
    //}

    bool NumberInputValue::IsValueValid()
    {
        // Call the base class to validate isRequired
        /* boolean isValid;
         RETURN_IF_FAILED(InputValue::IsValueValid(&isValid));

         ComPtr<ABI::Windows::Foundation::IReference<double>> max;
         RETURN_IF_FAILED(m_adaptiveNumberInput->get_Max(&max));

         ComPtr<ABI::Windows::Foundation::IReference<double>> min;
         RETURN_IF_FAILED(m_adaptiveNumberInput->get_Min(&min));

         HString currentValue;
         RETURN_IF_FAILED(get_CurrentValue(currentValue.GetAddressOf()));*/
        bool isValid = InputValue::IsValueValid();
        auto max = m_adaptiveNumberInput.Max();
        auto min = m_adaptiveNumberInput.Min();
        auto currentValue = CurrentValue();

        // If there is a value, confirm that it's a number and within the min/max range
        if (!currentValue.empty())
        {
            try
            {
                const std::string currentValueStdString = HStringToUTF8(currentValue);
                double currentDouble = std::stod(currentValueStdString);

                if (max)
                {
                    /*  double maxDouble;
                      RETURN_IF_FAILED(max->get_Value(&maxDouble));*/
                    double maxDouble = max.Value();
                    isValid &= (currentDouble <= maxDouble);
                }

                if (min)
                {
                    /*double minDouble;
                    RETURN_IF_FAILED(min->get_Value(&minDouble));*/
                    double minDouble = min.Value();
                    isValid &= (currentDouble >= minDouble);
                }
            }
            catch (...)
            {
                // If stoi failed this isn't a valid number
                isValid = false;
            }
        }

        return isValid;
    }

    /* HRESULT DateInputValue::RuntimeClassInitialize(_In_ IAdaptiveDateInput* adaptiveDateInput,
                                                    _In_ ICalendarDatePicker* uiDatePickerElement,
                                                    _In_ IBorder* validationBorder)
     {
         m_adaptiveDateInput = adaptiveDateInput;
         m_datePickerElement = uiDatePickerElement;

         Microsoft::WRL::ComPtr<IAdaptiveInputElement> dateInputAsAdaptiveInput;
         RETURN_IF_FAILED(m_adaptiveDateInput.As(&dateInputAsAdaptiveInput));

         ComPtr<IUIElement> datePickerAsUIElement;
         RETURN_IF_FAILED(m_datePickerElement.As(&datePickerAsUIElement));

         RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(dateInputAsAdaptiveInput.Get(),
     datePickerAsUIElement.Get(), validationBorder));

         return S_OK;
     }*/

    DateInputValue::DateInputValue(rtom::AdaptiveDateInput const& adaptiveDateInput,
                                   rtxaml::Controls::CalendarDatePicker const& uiDatePickerElement,
                                   rtxaml::Controls::Border const& validationBorder) :
        InputValue(adaptiveDateInput, uiDatePickerElement, validationBorder),
        m_adaptiveDateInput(adaptiveDateInput), m_datePickerElement(uiDatePickerElement)
    {
    }

    winrt::hstring DateInputValue::CurrentValue()
    {
        /*ComPtr<IReference<DateTime>> dateRef;
        RETURN_IF_FAILED(m_datePickerElement->get_Date(&dateRef));*/
        auto dateRef = m_datePickerElement.Date();

        winrt::hstring formattedDate{};
        if (dateRef != nullptr)
        {
            /*DateTime date;
            RETURN_IF_FAILED(dateRef->get_Value(&date));*/
            auto date = dateRef.Value();
            /*ComPtr<IDateTimeFormatterFactory> dateTimeFactory;
            RETURN_IF_FAILED(GetActivationFactory(
                HStringReference(RuntimeClass_Windows_Globalization_DateTimeFormatting_DateTimeFormatter).Get(), &dateTimeFactory));*/

            /* ComPtr<IDateTimeFormatter> dateTimeFormatter;
             RETURN_IF_FAILED(dateTimeFactory->CreateDateTimeFormatter
                 HStringReference(L"{year.full}-{month.integer(2)}-{day.integer(2)}").Get(), &dateTimeFormatter));*/
            winrt::Windows::Globalization::DateTimeFormatting::DateTimeFormatter dateTimeFormatter{
                L"{year.full}-{month.integer(2)}-{day.integer(2)}"};

            /*RETURN_IF_FAILED(dateTimeFormatter->Format(date, formattedDate.GetAddressOf()));*/
            formattedDate = dateTimeFormatter.Format(date);
        }

        return formattedDate;
    }

    /*HRESULT TimeInputValue::RuntimeClassInitialize(_In_ IAdaptiveTimeInput* adaptiveTimeInput,
                                                   _In_ ITimePicker* uiTimePickerElement,
                                                   _In_ IBorder* validationBorder)
    {
        m_adaptiveTimeInput = adaptiveTimeInput;
        m_timePickerElement = uiTimePickerElement;

        Microsoft::WRL::ComPtr<IAdaptiveInputElement> timeInputAsAdaptiveInput;
        RETURN_IF_FAILED(m_adaptiveTimeInput.As(&timeInputAsAdaptiveInput));

        ComPtr<IUIElement> timePickerAsUIElement;
        RETURN_IF_FAILED(m_timePickerElement.As(&timePickerAsUIElement));

        RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(timeInputAsAdaptiveInput.Get(), timePickerAsUIElement.Get(),
    validationBorder)); return S_OK;
    }*/

    TimeInputValue::TimeInputValue(rtom::AdaptiveTimeInput adaptiveTimeInput,
                                   rtxaml::Controls::TimePicker uiTimePickerElement,
                                   rtxaml::Controls::Border validationBorder) :
        InputValue(adaptiveTimeInput, uiTimePickerElement, validationBorder),
        m_adaptiveTimeInput(adaptiveTimeInput), m_timePickerElement(uiTimePickerElement)
    {
    }

    winrt::hstring TimeInputValue::CurrentValue()
    {
        /* ComPtr<ITimePicker3> timePicker3;
         RETURN_IF_FAILED(m_timePickerElement.As(&timePicker3));*/

        /* ComPtr<IReference<TimeSpan>> timeSpanReference;
         RETURN_IF_FAILED(timePicker3->get_SelectedTime(&timeSpanReference));*/

        auto timeSpanReference = m_timePickerElement.SelectedTime();

        char buffer[6] = {0};

        if (timeSpanReference != nullptr)
        {
            /*TimeSpan timeSpan;
            RETURN_IF_FAILED(timeSpanReference->get_Value(&timeSpan));*/
            // timeSpan here is std::chrono::duration<int64_t, 100 * std::nano>, so count will give the same value as duration before
            auto timeSpan = timeSpanReference.Value();

            // TODO: Is is the same number?
            uint64_t totalMinutes = timeSpan.count() / 10000000 / 60;
            uint64_t hours = totalMinutes / 60;
            uint64_t minutesPastTheHour = totalMinutes - (hours * 60);

            sprintf_s(buffer, sizeof(buffer), "%02llu:%02llu", hours, minutesPastTheHour);
        }

        return UTF8ToHString(std::string(buffer));
    }

    bool TimeInputValue::IsValueValid()
    {
        // Call the base class to validate isRequired
        /*boolean isBaseValid;
        RETURN_IF_FAILED(InputValue::IsValueValid(&isBaseValid));*/
        bool isBaseValid = InputValue::IsValueValid();

        // If time is set, validate max and min
        bool isMaxMinValid = true;

        /*ComPtr<ITimePicker3> timePicker3;
        RETURN_IF_FAILED(m_timePickerElement.As(&timePicker3));

        ComPtr<IReference<TimeSpan>> timeSpanReference;
        RETURN_IF_FAILED(timePicker3->get_SelectedTime(&timeSpanReference));*/
        auto timeSpanReference = m_timePickerElement.SelectedTime();

        if (isBaseValid && (timeSpanReference != nullptr))
        {
            /*TimeSpan currentTime;
            RETURN_IF_FAILED(timeSpanReference->get_Value(&currentTime));*/
            auto currentTime = timeSpanReference.Value();

            /*HString minTimeString;
            RETURN_IF_FAILED(m_adaptiveTimeInput->get_Min(minTimeString.GetAddressOf()));*/
            auto minTimeString = m_adaptiveTimeInput.Min();
            if (!minTimeString.empty())
            {
                std::string minTimeStdString = HStringToUTF8(minTimeString);
                unsigned int minHours, minMinutes;
                if (::AdaptiveCards::DateTimePreparser::TryParseSimpleTime(minTimeStdString, minHours, minMinutes))
                {
                    /*TimeSpan minTime{(INT64)(minHours * 60 + minMinutes) * 10000000 * 60};*/
                    // TODO: Can we make it look nicer? this is rather ugly
                    winrt::Windows::Foundation::TimeSpan minTime{(int64_t)(minHours * 60 + minMinutes) * 1000000 * 60};
                    isMaxMinValid &= currentTime.count() >= minTime.count();
                }
            }

            /*HString maxTimeString;
            RETURN_IF_FAILED(m_adaptiveTimeInput->get_Max(maxTimeString.GetAddressOf()));*/
            auto maxTimeString = m_adaptiveTimeInput.Max();
            if (!maxTimeString.empty())
            {
                std::string maxTimeStdString = HStringToUTF8(maxTimeString);
                unsigned int maxHours, maxMinutes;
                if (::AdaptiveCards::DateTimePreparser::TryParseSimpleTime(maxTimeStdString, maxHours, maxMinutes))
                {
                    winrt::Windows::Foundation::TimeSpan maxTime{(int64_t)(maxHours * 60 + maxMinutes) * 10000000 * 60};
                    isMaxMinValid &= currentTime.count() <= maxTime.count();
                }
            }
        }
        return isBaseValid && isMaxMinValid;
    }

    /* HRESULT ToggleInputValue::RuntimeClassInitialize(_In_ IAdaptiveToggleInput* adaptiveToggleInput,
                                                      _In_ ICheckBox* uiCheckBoxElement,
                                                      _In_ IBorder* validationBorder)
     {
         m_adaptiveToggleInput = adaptiveToggleInput;
         m_checkBoxElement = uiCheckBoxElement;

         Microsoft::WRL::ComPtr<IAdaptiveInputElement> toggleInputAsAdaptiveInput;
         RETURN_IF_FAILED(m_adaptiveToggleInput.As(&toggleInputAsAdaptiveInput));

         ComPtr<IUIElement> checkBoxAsUIElement;
         RETURN_IF_FAILED(m_checkBoxElement.As(&checkBoxAsUIElement));

         RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(toggleInputAsAdaptiveInput.Get(),
     checkBoxAsUIElement.Get(), validationBorder)); return S_OK;
     }*/

    ToggleInputValue::ToggleInputValue(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveToggleInput adaptiveToggleInput,
                                       winrt::Windows::UI::Xaml::Controls::CheckBox uiCheckBoxElement,
                                       winrt::Windows::UI::Xaml::Controls::Border validationBorder) :
        InputValue(adaptiveToggleInput, uiCheckBoxElement, validationBorder),
        m_adaptiveToggleInput(adaptiveToggleInput), m_checkBoxElement(uiCheckBoxElement)
    {
    }

    winrt::hstring ToggleInputValue::CurrentValue()
    {
        /* boolean checkedValue = false;
         XamlHelpers::GetToggleValue(m_checkBoxElement.Get(), &checkedValue);*/
        auto checkedValue = XamlHelpers::GetToggleValue(m_checkBoxElement);

        if (checkedValue)
        {
            return m_adaptiveToggleInput.ValueOn();
        }
        else
        {
            return m_adaptiveToggleInput.ValueOff();
        }
    }

    bool ToggleInputValue::IsValueValid()
    {
        // Don't use the base class IsValueValid to validate required for toggle. That method counts required as
        // satisfied if any value is set, but for toggle required means the check box is checked. An unchecked value
        // will still have a value (either false, or whatever's in valueOff).
        /* boolean isRequired;
         RETURN_IF_FAILED(m_adaptiveInputElement->get_IsRequired(&isRequired))*/
        auto isRequired = m_adaptiveInputElement.IsRequired();

        bool meetsRequirement = true;
        if (isRequired)
        {
            // MeetsRequirement is true if toggle is checked
            meetsRequirement = XamlHelpers::GetToggleValue(m_checkBoxElement);
        }
        return meetsRequirement;
    }

    std::string GetChoiceValue(rtom::AdaptiveChoiceSetInput const& choiceInput, uint32_t selectedIndex)
    {
        if (selectedIndex != -1)
        {
            /*ComPtr<IVector<AdaptiveChoiceInput*>> choices;
            THROW_IF_FAILED(choiceInput->get_Choices(&choices));*/
            auto choices = choiceInput.Choices();

            /*ComPtr<IAdaptiveChoiceInput> choice;
            THROW_IF_FAILED(choices->GetAt(selectedIndex, &choice));*/
            // TODO: should we check if selectedIndex is a valid index? And if not, should we log an error / throw an exception?
            auto choice = choices.GetAt(selectedIndex);
            /*HString value;
            THROW_IF_FAILED(choice->get_Value(value.GetAddressOf()));*/

            return HStringToUTF8(choice.Value());
        }
        return "";
    }

    /*HRESULT CompactChoiceSetInputValue::RuntimeClassInitialize(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                               _In_ ISelector* choiceSetSelectorElement,
                                                               _In_ IBorder* validationBorder)
    {
        m_adaptiveChoiceSetInput = adaptiveChoiceSetInput;
        m_selectorElement = choiceSetSelectorElement;

        Microsoft::WRL::ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
        RETURN_IF_FAILED(m_adaptiveChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));

        Microsoft::WRL::ComPtr<IUIElement> selectorAsUIElement;
        m_selectorElement.As(&selectorAsUIElement);

        RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(choiceSetInputAsAdaptiveInput.Get(),
    selectorAsUIElement.Get(), validationBorder)); return S_OK;
    }*/

    CompactChoiceSetInputValue::CompactChoiceSetInputValue(rtom::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                                           rtxaml::Controls::Primitives::Selector choiceSetSelector,
                                                           rtxaml::Controls::Border validationBorder) :
        InputValue(adaptiveChoiceSetInput, choiceSetSelector, validationBorder),
        m_adaptiveChoiceSetInput(adaptiveChoiceSetInput), m_selectorElement(choiceSetSelector)
    {
    }

    winrt::hstring CompactChoiceSetInputValue::CurrentValue()
    {
        /*ABI::AdaptiveCards::ObjectModel::WinUI3::ChoiceSetStyle choiceSetStyle;
        RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_ChoiceSetStyle(&choiceSetStyle));*/
        auto choiceSetStyle = m_adaptiveChoiceSetInput.ChoiceSetStyle();

        // boolean isMultiSelect;
        // RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));
        auto isMultiSelect = m_adaptiveChoiceSetInput.IsMultiSelect();

        // INT32 selectedIndex;
        // RETURN_IF_FAILED(m_selectorElement->get_SelectedIndex(&selectedIndex));
        auto selectedIndex = m_selectorElement.SelectedIndex();

        std::string choiceValue = GetChoiceValue(m_adaptiveChoiceSetInput, selectedIndex);
        return UTF8ToHString(choiceValue);
    }

    /*HRESULT ExpandedChoiceSetInputValue::RuntimeClassInitialize(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                                _In_ IPanel* choiceSetPanelElement,
                                                                _In_ IBorder* validationBorder)
    {
        m_adaptiveChoiceSetInput = adaptiveChoiceSetInput;
        m_panelElement = choiceSetPanelElement;

        Microsoft::WRL::ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
        RETURN_IF_FAILED(m_adaptiveChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));

        Microsoft::WRL::ComPtr<IUIElement> panelAsUIElement;
        m_panelElement.As(&panelAsUIElement);

        RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(choiceSetInputAsAdaptiveInput.Get(), panelAsUIElement.Get(),
    validationBorder)); return S_OK;
    }*/

    ExpandedChoiceSetInputValue::ExpandedChoiceSetInputValue(rtom::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                                             rtxaml::Controls::Panel choiceSetPanelElement,
                                                             rtxaml::Controls::Border validationBorder) :
        InputValue(adaptiveChoiceSetInput, choiceSetPanelElement, validationBorder),
        m_adaptiveChoiceSetInput(adaptiveChoiceSetInput), m_panelElement(choiceSetPanelElement)
    {
    }

    winrt::hstring ExpandedChoiceSetInputValue::CurrentValue()
    {
        // Get the panel children
        /*ComPtr<IVector<UIElement*>> panelChildren;
        RETURN_IF_FAILED(m_panelElement->get_Children(panelChildren.ReleaseAndGetAddressOf()));*/
        auto panelChildren = m_panelElement.Children();

        // UINT size;
        // RETURN_IF_FAILED(panelChildren->get_Size(&size));
        auto size = panelChildren.Size();

        // boolean isMultiSelect;
        // RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));
        auto isMultiSelect = m_adaptiveChoiceSetInput.IsMultiSelect();

        if (isMultiSelect)
        {
            // For multiselect, gather all the inputs in a comma delimited list
            std::string multiSelectValues;
            /*for (UINT i = 0; i < size; i++)
            {
                ComPtr<IUIElement> currentElement;
                RETURN_IF_FAILED(panelChildren->GetAt(i, &currentElement));

                boolean checkedValue = false;
                XamlHelpers::GetToggleValue(currentElement.Get(), &checkedValue);

                if (checkedValue)
                {
                    std::string choiceValue = GetChoiceValue(m_adaptiveChoiceSetInput.Get(), i);
                    multiSelectValues += choiceValue + ",";
                }
            }*/
            uint32_t index = 0;
            for (auto element : panelChildren)
            {
                if (XamlHelpers::GetToggleValue(element))
                {
                    multiSelectValues += GetChoiceValue(m_adaptiveChoiceSetInput, index) + ",";
                }
            }

            if (!multiSelectValues.empty())
            {
                multiSelectValues = multiSelectValues.substr(0, (multiSelectValues.size() - 1));
            }
            return UTF8ToHString(multiSelectValues);
        }
        else
        {
            // Look for the single selected choice
            /* INT32 selectedIndex = -1;
             for (UINT i = 0; i < size; i++)
             {
                 ComPtr<IUIElement> currentElement;
                 RETURN_IF_FAILED(panelChildren->GetAt(i, &currentElement));

                 boolean checkedValue = false;
                 XamlHelpers::GetToggleValue(currentElement.Get(), &checkedValue);

                 if (checkedValue)
                 {
                     selectedIndex = i;
                     break;
                 }
             }*/
            uint32_t index = 0;
            uint32_t selectedIndex = -1;
            for (auto element : panelChildren)
            {
                if (XamlHelpers::GetToggleValue(element))
                {
                    selectedIndex = index;
                    break;
                }
            }
            /*std::string choiceValue = GetChoiceValue(m_adaptiveChoiceSetInput, selectedIndex);
            RETURN_IF_FAILED(UTF8ToHString(choiceValue, serializedUserInput));*/
            // TODO: Bad readability right?
            return UTF8ToHString(GetChoiceValue(m_adaptiveChoiceSetInput, selectedIndex));
        }
    }

    void ExpandedChoiceSetInputValue::SetFocus()
    {
        // Put focus on the first choice in the choice set
        /*ComPtr<IVector<UIElement*>> panelChildren;
        RETURN_IF_FAILED(m_panelElement->get_Children(panelChildren.ReleaseAndGetAddressOf()));*/
        auto panelChildren = m_panelElement.Children();

        // ComPtr<IUIElement> firstChoice;
        // RETURN_IF_FAILED(panelChildren->GetAt(0, &firstChoice));
        auto firstChoice = panelChildren.GetAt(0);

        // ComPtr<IControl> choiceAsControl;
        // RETURN_IF_FAILED(firstChoice.As(&choiceAsControl));

        if (const auto choiceAsControl = firstChoice.try_as<rtxaml::Controls::Control>())
        {
            // TODO: do we need to return bool indicating where focus was set?
            choiceAsControl.Focus(rtxaml::FocusState::Programmatic);
        }
    }

    /*HRESULT FilteredChoiceSetInputValue::RuntimeClassInitialize(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                                _In_ IAutoSuggestBox* autoSuggestBox,
                                                                _In_ IBorder* validationBorder)
    {
        m_adaptiveChoiceSetInput = adaptiveChoiceSetInput;
        m_autoSuggestBox = autoSuggestBox;

        Microsoft::WRL::ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
        RETURN_IF_FAILED(m_adaptiveChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));

        Microsoft::WRL::ComPtr<IUIElement> autoSuggestBoxAsUIElement;
        RETURN_IF_FAILED(m_autoSuggestBox.As(&autoSuggestBoxAsUIElement));

        RETURN_IF_FAILED(
            InputValue::RuntimeClassInitialize(choiceSetInputAsAdaptiveInput.Get(), autoSuggestBoxAsUIElement.Get(),
    validationBorder)); return S_OK;
    }*/

    FilteredChoiceSetInputValue::FilteredChoiceSetInputValue(rtom::AdaptiveChoiceSetInput adaptiveChoiceSetInput,
                                                             rtxaml::Controls::AutoSuggestBox autoSuggestBox,
                                                             rtxaml::Controls::Border validationBorder) :
        InputValue(adaptiveChoiceSetInput, autoSuggestBox, validationBorder),
        m_adaptiveChoiceSetInput(adaptiveChoiceSetInput), m_autoSuggestBox(autoSuggestBox)
    {
    }

    winrt::hstring FilteredChoiceSetInputValue::CurrentValue()
    {
        /* ComPtr<IVector<AdaptiveChoiceInput*>> choices;
         RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_Choices(&choices));*/
        auto choices = m_adaptiveChoiceSetInput.Choices();

        // ComPtr<IAdaptiveChoiceInput> selectedChoice;
        // RETURN_IF_FAILED(GetSelectedChoice(&selectedChoice));
        auto selectedChoice = GetSelectedChoice();
        if (selectedChoice != nullptr)
        {
            /*RETURN_IF_FAILED(selectedChoice->get_Value(serializedUserInput));*/
            return selectedChoice.Value();
        }

        // TODO: is this correct to return empty hstring?
        return L"";
    }

    bool FilteredChoiceSetInputValue::IsValueValid()
    {
        bool isValid;

        // Check if there's text in the autoSuggestBox
        /* HString textHString;
         RETURN_IF_FAILED(m_autoSuggestBox->get_Text(textHString.GetAddressOf()));*/
        auto textHString = m_autoSuggestBox.Text();
        if (textHString.empty())
        {
            // Empty input is only valid if it's not required
            /*boolean isRequired;
            RETURN_IF_FAILED(m_adaptiveInputElement->get_IsRequired(&isRequired));*/
            auto isRequired = m_adaptiveInputElement.IsRequired();
            isValid = !isRequired;
        }
        else
        {
            // Non-empty input must match one of the exisiting choices
            /*ComPtr<IAdaptiveChoiceInput> selectedChoice;
            RETURN_IF_FAILED(GetSelectedChoice(&selectedChoice));*/
            auto selectedChoice = GetSelectedChoice();
            isValid = (selectedChoice != nullptr);
        }

        return isValid;
    }

    rtom::AdaptiveChoiceInput FilteredChoiceSetInputValue::GetSelectedChoice()
    {
        /*HString textHString;
        RETURN_IF_FAILED(m_autoSuggestBox->get_Text(textHString.GetAddressOf()));*/
        auto textHString = m_autoSuggestBox.Text();
        std::string text = HStringToUTF8(textHString);

        /*ComPtr<IVector<AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_Choices(&choices));*/
        auto choices = m_adaptiveChoiceSetInput.Choices();

       /* ComPtr<IAdaptiveChoiceInput> selectedChoice;
        IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(),
            [&selectedChoice, text](IAdaptiveChoiceInput* choice)
            {
                HString titleHString;
                RETURN_IF_FAILED(choice->get_Title(titleHString.GetAddressOf()));

                std::string title = HStringToUTF8(titleHString.Get());

                if (!ParseUtil::ToLowercase(text).compare(ParseUtil::ToLowercase(title)))
                {
                    selectedChoice = choice;
                }

                return S_OK;
            });*/
        // TODO: I'm not missing anything here, right? IterateOverVector is not neccessary
        rtom::AdaptiveChoiceInput selectedChoice{nullptr};
        for (auto choice: choices)
        {
            auto titleHString = choice.Title();

            std::string title = HStringToUTF8(titleHString);

            if (!::AdaptiveCards::ParseUtil::ToLowercase(text).compare(::AdaptiveCards::ParseUtil::ToLowercase(title)))
            {
                selectedChoice = choice;
                // TODO: do we need to break here?
                break;
            }
        }

        return selectedChoice;
    }
}
