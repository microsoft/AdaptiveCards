#include "pch.h"
#include "InputItem.h"
#include "XamlHelpers.h"
#include <windows.globalization.datetimeformatting.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Globalization::DateTimeFormatting;
using namespace ABI::Windows::UI::Xaml; 
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace AdaptiveCards::XamlCardRenderer;

void InputItem::SerializeTextInput(
    Json::Value& jsonValue,
    const char * idString)
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

    jsonValue[idString] = textString.c_str();
}

void InputItem::SerializeDateInput(
    Json::Value& jsonValue,
    const char * idString)
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

        ComPtr<IDateTimeFormatterStatics> dateTimeStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Globalization_DateTimeFormatting_DateTimeFormatter).Get(), &dateTimeStatics));

        // TODO: Confirm desired date format
        ComPtr<IDateTimeFormatter> dateTimeFormatter;
        THROW_IF_FAILED(dateTimeStatics->get_ShortDate(&dateTimeFormatter));

        HString formattedDate;
        THROW_IF_FAILED(dateTimeFormatter->Format(date, formattedDate.GetAddressOf()));

        THROW_IF_FAILED(HStringToUTF8(formattedDate.Get(), value));
    }

    jsonValue[idString] = value;
}

void InputItem::SerializeTimeInput(
    Json::Value& jsonValue,
    const char * idString)
{
    ComPtr<ITimePicker> timePicker;
    THROW_IF_FAILED(m_uiInputElement.As(&timePicker));

    TimeSpan timeSpan;
    THROW_IF_FAILED(timePicker->get_Time(&timeSpan));

    UINT64 totalMinutes = timeSpan.Duration / 10000000 / 60;
    UINT64 hours = totalMinutes / 60;
    UINT64 minutesPastTheHour = totalMinutes - (hours * 60);

    // TODO: Confirm desired time format
    char buffer[6];
    sprintf_s(buffer, sizeof(buffer), "%02llu:%02llu", hours, minutesPastTheHour);

    jsonValue[idString] = buffer;
}

void InputItem::SerializeToggleInput(
    Json::Value& jsonValue,
    const char * idString)
{
    boolean checkedValue = false;
    XamlHelpers::GetToggleValue(m_uiInputElement.Get(), &checkedValue);

    ComPtr<IAdaptiveInputToggle> toggleInput;
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

    jsonValue[idString] = utf8Value;
}

void InputItem::GetChoiceValue(
    IAdaptiveInputChoiceSet* choiceInput,
    INT32 selectedIndex,
    std::string& choiceValue)
{
    if (selectedIndex != -1)
    {
        ComPtr<IVector<IAdaptiveInputChoice*>> choices;
        THROW_IF_FAILED(choiceInput->get_Choices(&choices));

        ComPtr<IAdaptiveInputChoice> choice;
        THROW_IF_FAILED(choices->GetAt(selectedIndex, &choice));

        HString value;
        THROW_IF_FAILED(choice->get_Value(value.GetAddressOf()));

        THROW_IF_FAILED(HStringToUTF8(value.Get(), choiceValue));
    }
}

void InputItem::SerializeChoiceSetInput(
    Json::Value& jsonValue,
    const char * idString)
{
    ComPtr<IAdaptiveInputChoiceSet> choiceInput;
    THROW_IF_FAILED(m_adaptiveInputElement.As(&choiceInput));

    ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle choiceSetStyle;
    THROW_IF_FAILED(choiceInput->get_ChoiceSetStyle(&choiceSetStyle));

    boolean isMultiSelect;
    THROW_IF_FAILED(choiceInput->get_IsMultiSelect(&isMultiSelect));

    if (choiceSetStyle == ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle_Compact && !isMultiSelect)
    {
        // Handle compact style
        ComPtr<ISelector> selector;
        THROW_IF_FAILED(m_uiInputElement.As(&selector));

        INT32 selectedIndex;
        THROW_IF_FAILED(selector->get_SelectedIndex(&selectedIndex));

        std::string choiceValue;
        GetChoiceValue(choiceInput.Get(), selectedIndex, choiceValue);
        jsonValue[idString] = choiceValue;
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
            // For multiselect, gather all the inputs in a Json::arrayValue
            Json::Value multiSelectValues(Json::arrayValue);
            for (UINT i = 0; i < size; i++)
            {
                ComPtr<IUIElement> currentElement;
                THROW_IF_FAILED(panelChildren->GetAt(i, &currentElement));

                boolean checkedValue = false;
                XamlHelpers::GetToggleValue(currentElement.Get(), &checkedValue);

                if (checkedValue)
                {
                    std::string choiceValue;
                    GetChoiceValue(choiceInput.Get(), i, choiceValue);
                    multiSelectValues.append(Json::Value(choiceValue.c_str()));
                }
            }
            jsonValue[idString] = multiSelectValues;
        }
        else
        {
            // Look for the single selected choice
            INT32 selectedIndex;
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
            std::string choiceValue;
            GetChoiceValue(choiceInput.Get(), selectedIndex, choiceValue);
            jsonValue[idString] = choiceValue;
        }
    }
}

void InputItem::Serialize(Json::Value & jsonValue)
{
    ComPtr<IAdaptiveCardElement> cardElement;
    THROW_IF_FAILED(m_adaptiveInputElement.As(&cardElement));

    ABI::AdaptiveCards::XamlCardRenderer::ElementType elementType;
    THROW_IF_FAILED(cardElement->get_ElementType(&elementType));

    HString id;
    THROW_IF_FAILED(m_adaptiveInputElement->get_Id(id.GetAddressOf()));

    std::string idString;
    THROW_IF_FAILED(HStringToUTF8(id.Get(), idString));

    switch (elementType)
    {
        case ElementType_InputText:
        case ElementType_InputNumber:
        {
            SerializeTextInput(jsonValue, idString.c_str());
            break;
        }
        case ElementType_InputDate:
        {
            SerializeDateInput(jsonValue, idString.c_str());
            break;
        }
        case ElementType_InputTime:
        {
            SerializeTimeInput(jsonValue, idString.c_str());
            break;
        }
        case ElementType_InputToggle:
        {
            SerializeToggleInput(jsonValue, idString.c_str());
            break;
        }
        case ElementType_InputChoiceSet:
        {
            SerializeChoiceSetInput(jsonValue, idString.c_str());
            break;
        }
    }
}
