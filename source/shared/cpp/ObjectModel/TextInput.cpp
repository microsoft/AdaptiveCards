#include "pch.h"
#include "ParseUtil.h"
#include "TextInput.h"

using namespace AdaptiveSharedNamespace;

TextInput::TextInput() :
    BaseInputElement(CardElementType::TextInput), m_isMultiline(false), m_maxLength(0), m_style(TextInputStyle::Text)
{
    PopulateKnownPropertiesSet();
}

Json::Value TextInput::SerializeToJsonValue() const
{
    Json::Value root = BaseInputElement::SerializeToJsonValue();

    if (m_isMultiline)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsMultiline)] = m_isMultiline;
    }

    if (m_maxLength != 0)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLength)] = m_maxLength;
    }

    if (!m_placeholder.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder)] = m_placeholder;
    }

    if (!m_value.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = m_value;
    }

    if (m_style != TextInputStyle::Text)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = TextInputStyleToString(m_style);
    }

    if (m_inlineAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::InlineAction)] =
            BaseCardElement::SerializeSelectAction(m_inlineAction);
    }

    return root;
}

std::string TextInput::GetPlaceholder() const
{
    return m_placeholder;
}

void TextInput::SetPlaceholder(const std::string& value)
{
    m_placeholder = value;
}

std::string TextInput::GetValue() const
{
    return m_value;
}

void TextInput::SetValue(const std::string& value)
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

TextInputStyle TextInput::GetTextInputStyle() const
{
    return m_style;
}

void TextInput::SetTextInputStyle(const TextInputStyle value)
{
    m_style = value;
}

std::shared_ptr<BaseActionElement> TextInput::GetInlineAction() const
{
    return m_inlineAction;
}

void TextInput::SetInlineAction(const std::shared_ptr<BaseActionElement> action)
{
    m_inlineAction = action;
}

std::shared_ptr<BaseCardElement> TextInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TextInput);

    std::shared_ptr<TextInput> textInput = BaseInputElement::Deserialize<TextInput>(context, json);
    context.PushElement({ textInput->GetId(), textInput->GetInternalId(), false});

    textInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    textInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));
    textInput->SetIsMultiline(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiline, false));
    textInput->SetMaxLength(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLength, 0));
    textInput->SetTextInputStyle(
        ParseUtil::GetEnumValue<TextInputStyle>(json, AdaptiveCardSchemaKey::Style, TextInputStyle::Text, TextInputStyleFromString));
    textInput->SetInlineAction(ParseUtil::GetAction(context, json, AdaptiveCardSchemaKey::InlineAction, false));
    context.PopElement();

    return textInput;
}

std::shared_ptr<BaseCardElement> TextInputParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return TextInputParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void TextInput::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Placeholder),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsMultiline),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLength),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TextInput)});
}
