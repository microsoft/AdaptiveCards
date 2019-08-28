// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseContext.h"
#include "RichTextElementProperties.h"

using namespace AdaptiveSharedNamespace;
RichTextElementProperties::RichTextElementProperties() :
    TextElementProperties(), m_italic(false), m_strikethrough(false), m_underline(false)
{
}

RichTextElementProperties::RichTextElementProperties(const TextConfig& config, const std::string& text, const std::string& language) :
    TextElementProperties(config, text, language), m_italic(false), m_strikethrough(false), m_underline(false)
{
}

Json::Value RichTextElementProperties::SerializeToJsonValue(Json::Value& root) const
{
    (void)TextElementProperties::SerializeToJsonValue(root);
    if (GetItalic())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Italic)] = true;
    }

    if (GetStrikethrough())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Strikethrough)] = true;
    }

    if (GetUnderline())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Underline)] = true;
    }

    return root;
}

bool RichTextElementProperties::GetItalic() const
{
    return m_italic;
}

void RichTextElementProperties::SetItalic(const bool value)
{
    m_italic = value;
}

bool RichTextElementProperties::GetStrikethrough() const
{
    return m_strikethrough;
}

void RichTextElementProperties::SetStrikethrough(const bool value)
{
    m_strikethrough = value;
}

bool RichTextElementProperties::GetUnderline() const
{
    return m_underline;
}

void RichTextElementProperties::SetUnderline(const bool value)
{
    m_underline = value;
}

void RichTextElementProperties::Deserialize(const ParseContext& context, const Json::Value& json)
{
    TextElementProperties::Deserialize(context, json);
    SetItalic(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Italic, false));
    SetStrikethrough(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Strikethrough, false));
    SetUnderline(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Underline, false));
}

void RichTextElementProperties::PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties)
{
    TextElementProperties::PopulateKnownPropertiesSet(knownProperties);
    knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Italic),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Strikethrough),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Underline)});
}
