// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "InputValue.h"
#include "json/json.h"
#include "XamlHelpers.h"
#include <windows.globalization.datetimeformatting.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Globalization::DateTimeFormatting;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Documents;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace AdaptiveCards::Rendering::Uwp;

HRESULT ValidateIfNeeded(IAdaptiveInputValue* inputValue)
{
    HString currentValue;
    RETURN_IF_FAILED(inputValue->get_CurrentValue(currentValue.GetAddressOf()));

    return inputValue->Validate(nullptr);
}

HRESULT InputValue::RuntimeClassInitialize(_In_ IAdaptiveInputElement* adaptiveInputElement,
                                           _In_ IUIElement* uiInputElement,
                                           _In_ IBorder* validationBorder)
{
    m_adaptiveInputElement = adaptiveInputElement;
    m_uiInputElement = uiInputElement;
    m_validationBorder = validationBorder;

    return S_OK;
}

HRESULT InputValue::Validate(_Out_ boolean* isInputValid)
{
    boolean isValid;
    RETURN_IF_FAILED(IsValueValid(&isValid));

    RETURN_IF_FAILED(SetValidation(isValid));

    if (isInputValid)
    {
        *isInputValid = isValid;
    }

    return S_OK;
}

HRESULT InputValue::SetFocus()
{
    // Set focus on the input control
    ComPtr<IControl> inputAsControl;
    RETURN_IF_FAILED(m_uiInputElement.As(&inputAsControl));

    boolean isFocused;
    RETURN_IF_FAILED(inputAsControl->Focus(FocusState_Programmatic, &isFocused));

    return S_OK;
}

HRESULT InputValue::SetAccessibilityProperties(boolean isInputValid)
{
    ComPtr<IAutomationPropertiesStatics5> automationPropertiesStatics;

    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                          &automationPropertiesStatics));

    // This smart pointer is created as the variable inputUIElementParentContainer may contain the border instead of the
    // actual element if validations are required. If these properties are set into the border then they are not mentioned.
    ComPtr<IUIElement> uiInputElement(m_uiInputElement);

    ComPtr<IDependencyObject> inputUIElementAsDependencyObject;
    RETURN_IF_FAILED(uiInputElement.As(&inputUIElementAsDependencyObject));

    ComPtr<IVector<DependencyObject*>> uiElementDescribers;
    RETURN_IF_FAILED(automationPropertiesStatics->GetDescribedBy(inputUIElementAsDependencyObject.Get(),
                                                                 uiElementDescribers.GetAddressOf()));

    ComPtr<IUIElement> uiValidationError(m_validationError);
    ComPtr<IDependencyObject> uiValidationErrorAsDependencyObject;
    RETURN_IF_FAILED(uiValidationError.As(&uiValidationErrorAsDependencyObject));

    UINT index{};
    boolean found{};
    RETURN_IF_FAILED(uiElementDescribers->IndexOf(uiValidationErrorAsDependencyObject.Get(), &index, &found));

    // If the error message is visible then the input element must be described by it, otherwise we try to remove it from the list of describers
    if (!isInputValid && !found)
    {
        RETURN_IF_FAILED(uiElementDescribers->Append(uiValidationErrorAsDependencyObject.Get()));
    }
    else if (isInputValid && found)
    {
        RETURN_IF_FAILED(uiElementDescribers->RemoveAt(index));
    }

    RETURN_IF_FAILED(automationPropertiesStatics->SetIsDataValidForForm(inputUIElementAsDependencyObject.Get(), isInputValid));

    return S_OK;
}

HRESULT InputValue::get_ErrorMessage(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** uiErrorMessage)
{
    return m_validationError.CopyTo(uiErrorMessage);
}

HRESULT InputValue::put_ErrorMessage(_In_ IUIElement* uiErrorMessage)
{
    m_validationError = uiErrorMessage;
    return S_OK;
}

HRESULT InputValue::IsValueValid(_Out_ boolean* isInputValid)
{
    boolean isRequired;
    RETURN_IF_FAILED(m_adaptiveInputElement->get_IsRequired(&isRequired));

    bool isRequiredValid = true;
    if (isRequired)
    {
        HString currentValue;
        RETURN_IF_FAILED(get_CurrentValue(currentValue.GetAddressOf()));

        isRequiredValid = currentValue.IsValid();
    }

    *isInputValid = isRequiredValid;
    return S_OK;
}

HRESULT InputValue::SetValidation(boolean isInputValid)
{
    // Show or hide the border
    if (m_validationBorder)
    {
        if (isInputValid)
        {
            RETURN_IF_FAILED(m_validationBorder->put_BorderThickness({0, 0, 0, 0}));
        }
        else
        {
            RETURN_IF_FAILED(m_validationBorder->put_BorderThickness({1, 1, 1, 1}));
        }
    }

    // Show or hide the error message
    if (m_validationError)
    {
        if (isInputValid)
        {
            RETURN_IF_FAILED(m_validationError->put_Visibility(Visibility_Collapsed));
        }
        else
        {
            RETURN_IF_FAILED(m_validationError->put_Visibility(Visibility_Visible));
        }

        RETURN_IF_FAILED(SetAccessibilityProperties(isInputValid));
    }

    return S_OK;
}

HRESULT InputValue::get_InputElement(_COM_Outptr_ IAdaptiveInputElement** inputElement)
{
    return m_adaptiveInputElement.CopyTo(inputElement);
}

HRESULT TextInputBase::RuntimeClassInitialize(_In_ IAdaptiveInputElement* adaptiveInput,
                                              _In_ ITextBox* uiTextBoxElement,
                                              _In_ IBorder* validationBorder)
{
    {
        m_textBoxElement = uiTextBoxElement;

        ComPtr<IUIElement> textBoxAsUIElement;
        RETURN_IF_FAILED(m_textBoxElement.As(&textBoxAsUIElement));

        RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(adaptiveInput, textBoxAsUIElement.Get(), validationBorder));

        return S_OK;
    }
}

HRESULT TextInputBase::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
{
    return m_textBoxElement->get_Text(serializedUserInput);
}

HRESULT TextInputValue::RuntimeClassInitialize(_In_ IAdaptiveTextInput* adaptiveTextInput,
                                               _In_ ITextBox* uiTextBoxElement,
                                               _In_ IBorder* validationBorder)
{
    m_adaptiveTextInput = adaptiveTextInput;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> textInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveTextInput.As(&textInputAsAdaptiveInput));

    RETURN_IF_FAILED(TextInputBase::RuntimeClassInitialize(textInputAsAdaptiveInput.Get(), uiTextBoxElement, validationBorder));

    return S_OK;
}

HRESULT TextInputValue::IsValueValid(_Out_ boolean* isInputValid)
{
    // Call the base class to validate isRequired
    boolean isBaseValid;
    RETURN_IF_FAILED(InputValue::IsValueValid(&isBaseValid));

    // Validate the regex if one exists
    HString regex;
    RETURN_IF_FAILED(m_adaptiveTextInput->get_Regex(regex.GetAddressOf()));

    HString currentValue;
    RETURN_IF_FAILED(get_CurrentValue(currentValue.GetAddressOf()));

    boolean isRegexValid = true;
    if (regex.IsValid() && currentValue.IsValid())
    {
        std::string stringPattern = HStringToUTF8(regex.Get());
        std::regex pattern(stringPattern);

        std::string currentValueStdString = HStringToUTF8(currentValue.Get());

        std::smatch matches;
        isRegexValid = std::regex_match(currentValueStdString, matches, pattern);
    }

    *isInputValid = isBaseValid && isRegexValid;

    return S_OK;
}

HRESULT NumberInputValue::RuntimeClassInitialize(_In_ IAdaptiveNumberInput* adaptiveNumberInput,
                                                 _In_ ITextBox* uiTextBoxElement,
                                                 _In_ IBorder* validationBorder)
{
    m_adaptiveNumberInput = adaptiveNumberInput;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> numberInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveNumberInput.As(&numberInputAsAdaptiveInput));
    RETURN_IF_FAILED(TextInputBase::RuntimeClassInitialize(numberInputAsAdaptiveInput.Get(), uiTextBoxElement, validationBorder));
    return S_OK;
}

HRESULT NumberInputValue::IsValueValid(_Out_ boolean* isInputValid)
{
    // Call the base class to validate isRequired
    boolean isValid;
    RETURN_IF_FAILED(InputValue::IsValueValid(&isValid));

    ComPtr<ABI::Windows::Foundation::IReference<double>> max;
    RETURN_IF_FAILED(m_adaptiveNumberInput->get_Max(&max));

    ComPtr<ABI::Windows::Foundation::IReference<double>> min;
    RETURN_IF_FAILED(m_adaptiveNumberInput->get_Min(&min));

    HString currentValue;
    RETURN_IF_FAILED(get_CurrentValue(currentValue.GetAddressOf()));

    // If there is a value, confirm that it's a number and within the min/max range
    if (currentValue.IsValid())
    {
        try
        {
            const std::string currentValueStdString = HStringToUTF8(currentValue.Get());
            double currentDouble = std::stod(currentValueStdString);

            if (max.Get())
            {
                double maxDouble;
                RETURN_IF_FAILED(max->get_Value(&maxDouble));
                isValid &= (currentDouble <= maxDouble);
            }

            if (min.Get())
            {
                double minDouble;
                RETURN_IF_FAILED(min->get_Value(&minDouble));
                isValid &= (currentDouble >= minDouble);
            }
        }
        catch (...)
        {
            // If stoi failed this isn't a valid number
            isValid = false;
        }
    }

    *isInputValid = isValid;

    return S_OK;
}

HRESULT DateInputValue::RuntimeClassInitialize(_In_ IAdaptiveDateInput* adaptiveDateInput,
                                               _In_ ICalendarDatePicker* uiDatePickerElement,
                                               _In_ IBorder* validationBorder)
{
    m_adaptiveDateInput = adaptiveDateInput;
    m_datePickerElement = uiDatePickerElement;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> dateInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveDateInput.As(&dateInputAsAdaptiveInput));

    ComPtr<IUIElement> datePickerAsUIElement;
    RETURN_IF_FAILED(m_datePickerElement.As(&datePickerAsUIElement));

    RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(dateInputAsAdaptiveInput.Get(), datePickerAsUIElement.Get(), validationBorder));

    return S_OK;
}

HRESULT DateInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
{
    ComPtr<IReference<DateTime>> dateRef;
    RETURN_IF_FAILED(m_datePickerElement->get_Date(&dateRef));

    HString formattedDate;
    if (dateRef != nullptr)
    {
        DateTime date;
        RETURN_IF_FAILED(dateRef->get_Value(&date));

        ComPtr<IDateTimeFormatterFactory> dateTimeFactory;
        RETURN_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Globalization_DateTimeFormatting_DateTimeFormatter).Get(), &dateTimeFactory));

        ComPtr<IDateTimeFormatter> dateTimeFormatter;
        RETURN_IF_FAILED(dateTimeFactory->CreateDateTimeFormatter(
            HStringReference(L"{year.full}-{month.integer(2)}-{day.integer(2)}").Get(), &dateTimeFormatter));

        RETURN_IF_FAILED(dateTimeFormatter->Format(date, formattedDate.GetAddressOf()));
    }

    RETURN_IF_FAILED(formattedDate.CopyTo(serializedUserInput));

    return S_OK;
}

HRESULT TimeInputValue::RuntimeClassInitialize(_In_ IAdaptiveTimeInput* adaptiveTimeInput,
                                               _In_ ITimePicker* uiTimePickerElement,
                                               _In_ IBorder* validationBorder)
{
    m_adaptiveTimeInput = adaptiveTimeInput;
    m_timePickerElement = uiTimePickerElement;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> timeInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveTimeInput.As(&timeInputAsAdaptiveInput));

    ComPtr<IUIElement> timePickerAsUIElement;
    RETURN_IF_FAILED(m_timePickerElement.As(&timePickerAsUIElement));

    RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(timeInputAsAdaptiveInput.Get(), timePickerAsUIElement.Get(), validationBorder));
    return S_OK;
}

HRESULT TimeInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
{
    ComPtr<ITimePicker3> timePicker3;
    RETURN_IF_FAILED(m_timePickerElement.As(&timePicker3));

    ComPtr<IReference<TimeSpan>> timeSpanReference;
    RETURN_IF_FAILED(timePicker3->get_SelectedTime(&timeSpanReference));

    char buffer[6] = {0};
    if (timeSpanReference != nullptr)
    {
        TimeSpan timeSpan;
        RETURN_IF_FAILED(timeSpanReference->get_Value(&timeSpan));

        UINT64 totalMinutes = timeSpan.Duration / 10000000 / 60;
        UINT64 hours = totalMinutes / 60;
        UINT64 minutesPastTheHour = totalMinutes - (hours * 60);

        sprintf_s(buffer, sizeof(buffer), "%02llu:%02llu", hours, minutesPastTheHour);
    }

    RETURN_IF_FAILED(UTF8ToHString(std::string(buffer), serializedUserInput));

    return S_OK;
}

HRESULT TimeInputValue::IsValueValid(_Out_ boolean* isInputValid)
{
    // Call the base class to validate isRequired
    boolean isBaseValid;
    RETURN_IF_FAILED(InputValue::IsValueValid(&isBaseValid));

    // If time is set, validate max and min
    boolean isMaxMinValid = true;

    ComPtr<ITimePicker3> timePicker3;
    RETURN_IF_FAILED(m_timePickerElement.As(&timePicker3));

    ComPtr<IReference<TimeSpan>> timeSpanReference;
    RETURN_IF_FAILED(timePicker3->get_SelectedTime(&timeSpanReference));

    if (isBaseValid && (timeSpanReference != nullptr))
    {
        TimeSpan currentTime;
        RETURN_IF_FAILED(timeSpanReference->get_Value(&currentTime));

        HString minTimeString;
        RETURN_IF_FAILED(m_adaptiveTimeInput->get_Min(minTimeString.GetAddressOf()));
        if (minTimeString.IsValid())
        {
            std::string minTimeStdString = HStringToUTF8(minTimeString.Get());
            unsigned int minHours, minMinutes;
            if (DateTimePreparser::TryParseSimpleTime(minTimeStdString, minHours, minMinutes))
            {
                TimeSpan minTime{(INT64)(minHours * 60 + minMinutes) * 10000000 * 60};
                isMaxMinValid &= currentTime.Duration >= minTime.Duration;
            }
        }

        HString maxTimeString;
        RETURN_IF_FAILED(m_adaptiveTimeInput->get_Max(maxTimeString.GetAddressOf()));
        if (maxTimeString.IsValid())
        {
            std::string maxTimeStdString = HStringToUTF8(maxTimeString.Get());
            unsigned int maxHours, maxMinutes;
            if (DateTimePreparser::TryParseSimpleTime(maxTimeStdString, maxHours, maxMinutes))
            {
                TimeSpan maxTime{(INT64)(maxHours * 60 + maxMinutes) * 10000000 * 60};
                isMaxMinValid &= currentTime.Duration <= maxTime.Duration;
            }
        }
    }
    *isInputValid = isBaseValid && isMaxMinValid;

    return S_OK;
}

HRESULT ToggleInputValue::RuntimeClassInitialize(_In_ IAdaptiveToggleInput* adaptiveToggleInput,
                                                 _In_ ICheckBox* uiCheckBoxElement,
                                                 _In_ IBorder* validationBorder)
{
    m_adaptiveToggleInput = adaptiveToggleInput;
    m_checkBoxElement = uiCheckBoxElement;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> toggleInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveToggleInput.As(&toggleInputAsAdaptiveInput));

    ComPtr<IUIElement> checkBoxAsUIElement;
    RETURN_IF_FAILED(m_checkBoxElement.As(&checkBoxAsUIElement));

    RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(toggleInputAsAdaptiveInput.Get(), checkBoxAsUIElement.Get(), validationBorder));
    return S_OK;
}

HRESULT ToggleInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
{
    boolean checkedValue = false;
    XamlHelpers::GetToggleValue(m_checkBoxElement.Get(), &checkedValue);

    HString value;
    if (checkedValue)
    {
        RETURN_IF_FAILED(m_adaptiveToggleInput->get_ValueOn(value.GetAddressOf()));
    }
    else
    {
        RETURN_IF_FAILED(m_adaptiveToggleInput->get_ValueOff(value.GetAddressOf()));
    }

    RETURN_IF_FAILED(value.CopyTo(serializedUserInput));

    return S_OK;
}

HRESULT ToggleInputValue::IsValueValid(_Out_ boolean* isInputValid)
{
    // Don't use the base class IsValueValid to validate required for toggle. That method counts required as satisfied
    // if any value is set, but for toggle required means the check box is checked. An unchecked value will still have
    // a value (either false, or whatever's in valueOff).
    boolean isRequired;
    RETURN_IF_FAILED(m_adaptiveInputElement->get_IsRequired(&isRequired));

    boolean meetsRequirement = true;
    if (isRequired)
    {
        boolean isToggleChecked = false;
        XamlHelpers::GetToggleValue(m_checkBoxElement.Get(), &isToggleChecked);

        meetsRequirement = isToggleChecked;
    }

    *isInputValid = meetsRequirement;

    return S_OK;
}

std::string GetChoiceValue(_In_ IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex)
{
    if (selectedIndex != -1)
    {
        ComPtr<IVector<AdaptiveChoiceInput*>> choices;
        THROW_IF_FAILED(choiceInput->get_Choices(&choices));

        ComPtr<IAdaptiveChoiceInput> choice;
        THROW_IF_FAILED(choices->GetAt(selectedIndex, &choice));

        HString value;
        THROW_IF_FAILED(choice->get_Value(value.GetAddressOf()));

        return HStringToUTF8(value.Get());
    }
    return "";
}

HRESULT CompactChoiceSetInputValue::RuntimeClassInitialize(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                           _In_ ISelector* choiceSetSelectorElement,
                                                           _In_ IBorder* validationBorder)
{
    m_adaptiveChoiceSetInput = adaptiveChoiceSetInput;
    m_selectorElement = choiceSetSelectorElement;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));

    Microsoft::WRL::ComPtr<IUIElement> selectorAsUIElement;
    m_selectorElement.As(&selectorAsUIElement);

    RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(choiceSetInputAsAdaptiveInput.Get(), selectorAsUIElement.Get(), validationBorder));
    return S_OK;
}

HRESULT CompactChoiceSetInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
try
{
    ABI::AdaptiveCards::ObjectModel::Uwp::ChoiceSetStyle choiceSetStyle;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_ChoiceSetStyle(&choiceSetStyle));

    boolean isMultiSelect;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));

    INT32 selectedIndex;
    RETURN_IF_FAILED(m_selectorElement->get_SelectedIndex(&selectedIndex));

    std::string choiceValue = GetChoiceValue(m_adaptiveChoiceSetInput.Get(), selectedIndex);
    RETURN_IF_FAILED(UTF8ToHString(choiceValue, serializedUserInput));

    return S_OK;
}
CATCH_RETURN;

HRESULT ExpandedChoiceSetInputValue::RuntimeClassInitialize(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                            _In_ IPanel* choiceSetPanelElement,
                                                            _In_ IBorder* validationBorder)
{
    m_adaptiveChoiceSetInput = adaptiveChoiceSetInput;
    m_panelElement = choiceSetPanelElement;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));

    Microsoft::WRL::ComPtr<IUIElement> panelAsUIElement;
    m_panelElement.As(&panelAsUIElement);

    RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(choiceSetInputAsAdaptiveInput.Get(), panelAsUIElement.Get(), validationBorder));
    return S_OK;
}

HRESULT ExpandedChoiceSetInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
try
{
    // Get the panel children
    ComPtr<IVector<UIElement*>> panelChildren;
    RETURN_IF_FAILED(m_panelElement->get_Children(panelChildren.ReleaseAndGetAddressOf()));

    UINT size;
    RETURN_IF_FAILED(panelChildren->get_Size(&size));

    boolean isMultiSelect;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));

    if (isMultiSelect)
    {
        // For multiselect, gather all the inputs in a comma delimited list
        std::string multiSelectValues;
        for (UINT i = 0; i < size; i++)
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
        }

        if (!multiSelectValues.empty())
        {
            multiSelectValues = multiSelectValues.substr(0, (multiSelectValues.size() - 1));
        }
        RETURN_IF_FAILED(UTF8ToHString(multiSelectValues, serializedUserInput));
    }
    else
    {
        // Look for the single selected choice
        INT32 selectedIndex = -1;
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
        }
        std::string choiceValue = GetChoiceValue(m_adaptiveChoiceSetInput.Get(), selectedIndex);
        RETURN_IF_FAILED(UTF8ToHString(choiceValue, serializedUserInput));
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT ExpandedChoiceSetInputValue::SetFocus()
{
    // Put focus on the first choice in the choice set
    ComPtr<IVector<UIElement*>> panelChildren;
    RETURN_IF_FAILED(m_panelElement->get_Children(panelChildren.ReleaseAndGetAddressOf()));

    ComPtr<IUIElement> firstChoice;
    RETURN_IF_FAILED(panelChildren->GetAt(0, &firstChoice));

    ComPtr<IControl> choiceAsControl;
    RETURN_IF_FAILED(firstChoice.As(&choiceAsControl));

    boolean isFocused;
    RETURN_IF_FAILED(choiceAsControl->Focus(FocusState_Programmatic, &isFocused));

    return S_OK;
}

HRESULT FilteredChoiceSetInputValue::RuntimeClassInitialize(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                            _In_ IAutoSuggestBox* autoSuggestBox,
                                                            _In_ IBorder* validationBorder)
{
    m_adaptiveChoiceSetInput = adaptiveChoiceSetInput;
    m_autoSuggestBox = autoSuggestBox;

    Microsoft::WRL::ComPtr<IAdaptiveInputElement> choiceSetInputAsAdaptiveInput;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput.As(&choiceSetInputAsAdaptiveInput));

    Microsoft::WRL::ComPtr<IUIElement> autoSuggestBoxAsUIElement;
    RETURN_IF_FAILED(m_autoSuggestBox.As(&autoSuggestBoxAsUIElement));

    RETURN_IF_FAILED(InputValue::RuntimeClassInitialize(choiceSetInputAsAdaptiveInput.Get(), autoSuggestBoxAsUIElement.Get(), validationBorder));
    return S_OK;
}

HRESULT FilteredChoiceSetInputValue::get_CurrentValue(_Outptr_ HSTRING* serializedUserInput)
try
{
    ComPtr<IVector<AdaptiveChoiceInput*>> choices;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_Choices(&choices));

    ComPtr<IAdaptiveChoiceInput> selectedChoice;
    RETURN_IF_FAILED(GetSelectedChoice(&selectedChoice));
    if (selectedChoice != nullptr)
    {
        RETURN_IF_FAILED(selectedChoice->get_Value(serializedUserInput));
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT FilteredChoiceSetInputValue::IsValueValid(boolean* isInputValid)
{
    boolean isValid;

    // Check if there's text in the autoSuggestBox
    HString textHString;
    RETURN_IF_FAILED(m_autoSuggestBox->get_Text(textHString.GetAddressOf()));
    if (!textHString.IsValid())
    {
        // Empty input is only valid if it's not required
        boolean isRequired;
        RETURN_IF_FAILED(m_adaptiveInputElement->get_IsRequired(&isRequired));
        isValid = !isRequired;
    }
    else
    {
        // Non-empty input must match one of the exisiting choices
        ComPtr<IAdaptiveChoiceInput> selectedChoice;
        RETURN_IF_FAILED(GetSelectedChoice(&selectedChoice));
        isValid = (selectedChoice != nullptr);
    }

    *isInputValid = isValid;

    return S_OK;
}

HRESULT FilteredChoiceSetInputValue::GetSelectedChoice(IAdaptiveChoiceInput** adaptiveChoiceInput)
{
    HString textHString;
    RETURN_IF_FAILED(m_autoSuggestBox->get_Text(textHString.GetAddressOf()));
    std::string text = HStringToUTF8(textHString.Get());

    ComPtr<IVector<AdaptiveChoiceInput*>> choices;
    RETURN_IF_FAILED(m_adaptiveChoiceSetInput->get_Choices(&choices));

    ComPtr<IAdaptiveChoiceInput> selectedChoice;
    IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(choices.Get(), [&selectedChoice, text](IAdaptiveChoiceInput* choice) {
        HString titleHString;
        RETURN_IF_FAILED(choice->get_Title(titleHString.GetAddressOf()));

        std::string title = HStringToUTF8(titleHString.Get());

        if (!ParseUtil::ToLowercase(text).compare(ParseUtil::ToLowercase(title)))
        {
            selectedChoice = choice;
        }

        return S_OK;
    });

    RETURN_IF_FAILED(selectedChoice.CopyTo(adaptiveChoiceInput));

    return S_OK;
}
