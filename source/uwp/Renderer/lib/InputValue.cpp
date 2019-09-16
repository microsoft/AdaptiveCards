// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "InputValue.h"
#include "json/json.h"
#include "XamlHelpers.h"
#include <windows.globalization.datetimeformatting.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Globalization::DateTimeFormatting;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace AdaptiveNamespace;

std::string InputValue::SerializeTextInput() const
{
    ComPtr<ITextBox> textBox;
    THROW_IF_FAILED(m_uiInputElement.As(&textBox));

    HString text;
    THROW_IF_FAILED(textBox->get_Text(text.GetAddressOf()));

    std::string textString;
    if (text.IsValid())
    {
        THROW_IF_FAILED(HStringToUTF8(text.Get(), textString));
    }

    return textString;
}

std::string InputValue::SerializeDateInput() const
{
    ComPtr<ICalendarDatePicker> datePicker;
    THROW_IF_FAILED(m_uiInputElement.As(&datePicker));

    ComPtr<IReference<DateTime>> dateRef;
    THROW_IF_FAILED(datePicker->get_Date(&dateRef));

    std::string value;
    if (dateRef != nullptr)
    {
        DateTime date;
        THROW_IF_FAILED(dateRef->get_Value(&date));

        ComPtr<IDateTimeFormatterFactory> dateTimeFactory;
        THROW_IF_FAILED(GetActivationFactory(
            HStringReference(RuntimeClass_Windows_Globalization_DateTimeFormatting_DateTimeFormatter).Get(), &dateTimeFactory));

        ComPtr<IDateTimeFormatter> dateTimeFormatter;
        THROW_IF_FAILED(dateTimeFactory->CreateDateTimeFormatter(
            HStringReference(L"{year.full}-{month.integer(2)}-{day.integer(2)}").Get(), &dateTimeFormatter));

        HString formattedDate;
        THROW_IF_FAILED(dateTimeFormatter->Format(date, formattedDate.GetAddressOf()));

        THROW_IF_FAILED(HStringToUTF8(formattedDate.Get(), value));
        return value;
    }
    return "";
}

std::string InputValue::SerializeTimeInput() const
{
    ComPtr<ITimePicker> timePicker;
    THROW_IF_FAILED(m_uiInputElement.As(&timePicker));

    TimeSpan timeSpan;
    THROW_IF_FAILED(timePicker->get_Time(&timeSpan));

    UINT64 totalMinutes = timeSpan.Duration / 10000000 / 60;
    UINT64 hours = totalMinutes / 60;
    UINT64 minutesPastTheHour = totalMinutes - (hours * 60);

    char buffer[6];
    sprintf_s(buffer, sizeof(buffer), "%02llu:%02llu", hours, minutesPastTheHour);

    return std::string(buffer);
}

std::string InputValue::SerializeToggleInput() const
{
    boolean checkedValue = false;
    XamlHelpers::GetToggleValue(m_uiInputElement.Get(), &checkedValue);

    ComPtr<IAdaptiveToggleInput> toggleInput;
    THROW_IF_FAILED(m_adaptiveInputElement.As(&toggleInput));

    HString value;
    if (checkedValue)
    {
        THROW_IF_FAILED(toggleInput->get_ValueOn(value.GetAddressOf()));
    }
    else
    {
        THROW_IF_FAILED(toggleInput->get_ValueOff(value.GetAddressOf()));
    }

    std::string utf8Value;
    THROW_IF_FAILED(HStringToUTF8(value.Get(), utf8Value));

    return utf8Value;
}

std::string InputValue::GetChoiceValue(_In_ IAdaptiveChoiceSetInput* choiceInput, INT32 selectedIndex) const
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

std::string InputValue::SerializeChoiceSetInput() const
{
    ComPtr<IAdaptiveChoiceSetInput> choiceInput;
    THROW_IF_FAILED(m_adaptiveInputElement.As(&choiceInput));

    ABI::AdaptiveNamespace::ChoiceSetStyle choiceSetStyle;
    THROW_IF_FAILED(choiceInput->get_ChoiceSetStyle(&choiceSetStyle));

    boolean isMultiSelect;
    THROW_IF_FAILED(choiceInput->get_IsMultiSelect(&isMultiSelect));

    if (choiceSetStyle == ABI::AdaptiveNamespace::ChoiceSetStyle_Compact && !isMultiSelect)
    {
        // Handle compact style
        ComPtr<ISelector> selector;
        THROW_IF_FAILED(m_uiInputElement.As(&selector));

        INT32 selectedIndex;
        THROW_IF_FAILED(selector->get_SelectedIndex(&selectedIndex));

        std::string choiceValue;
        return GetChoiceValue(choiceInput.Get(), selectedIndex);
    }
    else
    {
        // For expanded style, get the panel children
        ComPtr<IPanel> panel;
        THROW_IF_FAILED(m_uiInputElement.As(&panel));

        ComPtr<IVector<UIElement*>> panelChildren;
        THROW_IF_FAILED(panel->get_Children(panelChildren.ReleaseAndGetAddressOf()));

        UINT size;
        THROW_IF_FAILED(panelChildren->get_Size(&size));

        if (isMultiSelect)
        {
            // For multiselect, gather all the inputs in a comma delimited list
            std::string multiSelectValues;
            for (UINT i = 0; i < size; i++)
            {
                ComPtr<IUIElement> currentElement;
                THROW_IF_FAILED(panelChildren->GetAt(i, &currentElement));

                boolean checkedValue = false;
                XamlHelpers::GetToggleValue(currentElement.Get(), &checkedValue);

                if (checkedValue)
                {
                    std::string choiceValue = GetChoiceValue(choiceInput.Get(), i);
                    multiSelectValues += choiceValue + ",";
                }
            }

            if (!multiSelectValues.empty())
            {
                multiSelectValues = multiSelectValues.substr(0, (multiSelectValues.size() - 1));
            }
            return multiSelectValues;
        }
        else
        {
            // Look for the single selected choice
            INT32 selectedIndex = -1;
            for (UINT i = 0; i < size; i++)
            {
                ComPtr<IUIElement> currentElement;
                THROW_IF_FAILED(panelChildren->GetAt(i, &currentElement));

                boolean checkedValue = false;
                XamlHelpers::GetToggleValue(currentElement.Get(), &checkedValue);

                if (checkedValue)
                {
                    selectedIndex = i;
                    break;
                }
            }
            return GetChoiceValue(choiceInput.Get(), selectedIndex);
        }
    }
}

HRESULT InputValue::get_CurrentValue(_Outptr_ HSTRING* result)
{
    ComPtr<IAdaptiveCardElement> cardElement;
    RETURN_IF_FAILED(m_adaptiveInputElement.As(&cardElement));

    ABI::AdaptiveNamespace::ElementType elementType;
    RETURN_IF_FAILED(cardElement->get_ElementType(&elementType));

    std::string serializedInput;
    switch (elementType)
    {
    case ElementType_TextInput:
    case ElementType_NumberInput:
    {
        serializedInput = SerializeTextInput();
        break;
    }
    case ElementType_DateInput:
    {
        serializedInput = SerializeDateInput();
        break;
    }
    case ElementType_TimeInput:
    {
        serializedInput = SerializeTimeInput();
        break;
    }
    case ElementType_ToggleInput:
    {
        serializedInput = SerializeToggleInput();
        break;
    }
    case ElementType_ChoiceSetInput:
    {
        serializedInput = SerializeChoiceSetInput();
        break;
    }
    default:
        serializedInput = "";
        break;
    }

    RETURN_IF_FAILED(UTF8ToHString(serializedInput, result));

    return S_OK;
}

HRESULT InputValue::get_InputElement(_COM_Outptr_ IAdaptiveInputElement** inputElement)
{
    return m_adaptiveInputElement.CopyTo(inputElement);
}
