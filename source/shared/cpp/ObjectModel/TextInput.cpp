#include "ParseUtil.h"
#include "TextInput.h"

using namespace AdaptiveCards;

TextInput::TextInput() :
    BaseInputElement(CardElementType::TextInput),
    m_isMultiline(false),
    m_maxLength(0)
{
}

std::shared_ptr<TextInput> TextInput::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TextInput);

    std::shared_ptr<TextInput> textInput = BaseInputElement::Deserialize<TextInput>(json);

    textInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    textInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));
    textInput->SetIsMultiline(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiline, false));
    textInput->SetMaxLength(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLength, 0));
    textInput->SetTextInputStyle(ParseUtil::GetEnumValue<TextInputStyle>(json, AdaptiveCardSchemaKey::Style, TextInputStyle::Text, TextInputStyleFromString));

    return textInput;
}

std::shared_ptr<TextInput> TextInput::DeserializeFromString(const std::string& jsonString)
{
    return TextInput::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string TextInput::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value TextInput::SerializeToJsonValue()
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsMultiline)] = GetIsMultiline();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLength)] = GetMaxLength();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder)] = GetPlaceholder();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = GetValue();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = TextInputStyleToString(GetTextInputStyle());

    return root;
}

std::string TextInput::GetPlaceholder() const
{
    return m_placeholder;
}

void TextInput::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string TextInput::GetValue() const
{
    return m_value;
}

void TextInput::SetValue(const std::string value)
{
    m_value = value;
}

bool TextInput::GetIsMultiline() const
{
    return m_isMultiline;
}

void TextInput::SetIsMultiline(const bool value)
{
    m_isMultiline = value;
}

unsigned int TextInput::GetMaxLength() const
{
    return m_maxLength;
}

void TextInput::SetMaxLength(const unsigned int value)
{
    m_maxLength = value;
}

TextInputStyle AdaptiveCards::TextInput::GetTextInputStyle() const
{
    return m_style;
}

void AdaptiveCards::TextInput::SetTextInputStyle(const TextInputStyle value)
{
    m_style = value;
}
