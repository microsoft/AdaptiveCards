// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseUtil.h"
#include "TextInput.h"
#include "Util.h"

using namespace AdaptiveCards;

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

    if (!m_regex.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Regex)] = m_regex;
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

std::string TextInput::GetRegex() const
{
    return m_regex;
}

void TextInput::SetRegex(const std::string& value)
{
    m_regex = value;
}

std::shared_ptr<BaseCardElement> TextInputParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TextInput);

    std::shared_ptr<TextInput> textInput = BaseInputElement::Deserialize<TextInput>(context, json);
    textInput->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    textInput->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));
    textInput->SetMaxLength(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLength, 0));

    const auto isMultiline = ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiline, false);
    textInput->SetIsMultiline(isMultiline);

    const auto textInputStyle =
        ParseUtil::GetEnumValue<TextInputStyle>(json, AdaptiveCardSchemaKey::Style, TextInputStyle::Text, TextInputStyleFromString);
    textInput->SetTextInputStyle(textInputStyle);

    // emit warning in the case where style is `password` but multiline is specified (this is an invalid combination.
    // renderers should ignore multiline in this case)
    if (isMultiline && textInputStyle == TextInputStyle::Password)
    {
        context.warnings.emplace_back(
            std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidValue,
                                                       "Input.Text ignores isMultiline when using password style"));
    }

    textInput->SetInlineAction(ParseUtil::GetAction(context, json, AdaptiveCardSchemaKey::InlineAction, false));
    textInput->SetRegex(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Regex));

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
