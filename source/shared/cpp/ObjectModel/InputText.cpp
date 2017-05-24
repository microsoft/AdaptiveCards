#include "InputText.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

InputText::InputText() :
    BaseCardElement(CardElementType::InputText),
    m_isMultiline(false),
    m_maxLength(0)
{
}

std::shared_ptr<InputText> InputText::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::InputText);

    std::shared_ptr<InputText> inputText = BaseCardElement::Deserialize<InputText>(json);

    inputText->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    inputText->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));
    inputText->SetIsMultiline(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiline, false));
    inputText->SetMaxLength(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLength, 0));
    inputText->SetTextInputStyle(ParseUtil::GetEnumValue<TextInputStyle>(json, AdaptiveCardSchemaKey::Style, TextInputStyle::Text, TextInputStyleFromString));

    return inputText;
}

std::shared_ptr<InputText> InputText::DeserializeFromString(const std::string& jsonString)
{
    return InputText::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string InputText::Serialize()
{
    return "";
}

std::string InputText::GetPlaceholder() const
{
    return m_placeholder;
}

void InputText::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string InputText::GetValue() const
{
    return m_value;
}

void InputText::SetValue(const std::string value)
{
    m_value = value;
}

bool InputText::GetIsMultiline() const
{
    return m_isMultiline;
}

void InputText::SetIsMultiline(const bool value)
{
    m_isMultiline = value;
}

unsigned int InputText::GetMaxLength() const
{
    return m_maxLength;
}

void InputText::SetMaxLength(const unsigned int value)
{
    m_maxLength = value;
}

TextInputStyle AdaptiveCards::InputText::GetTextInputStyle() const
{
    return m_style;
}

void AdaptiveCards::InputText::SetTextInputStyle(const TextInputStyle value)
{
    m_style = value;
}
