// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "ParseContext.h"
#include "TextElementProperties.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

TextElementProperties::TextElementProperties() : m_language()
{
}

TextElementProperties::TextElementProperties(const TextStyleConfig& config, const std::string& text, const std::string& language) :
    m_textSize(config.size), m_textWeight(config.weight), m_fontType(config.fontType), m_textColor(config.color),
    m_isSubtle(config.isSubtle), m_language(language)
{
    SetText(text);
}

Json::Value TextElementProperties::SerializeToJsonValue(Json::Value& root) const
{
    if (m_textSize.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size)] =
            TextSizeToString(m_textSize.value_or(TextSize::Default));
    }

    if (m_textColor.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color)] =
            ForegroundColorToString(m_textColor.value_or(ForegroundColor::Default));
    }

    if (m_textWeight.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Weight)] =
            TextWeightToString(m_textWeight.value_or(TextWeight::Default));
    }

    if (m_fontType.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontType)] =
            FontTypeToString(m_fontType.value_or(FontType::Default));
    }

    if (m_isSubtle.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle)] = m_isSubtle.value_or(false);
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text)] = GetText();

    return root;
}

std::string TextElementProperties::GetText() const
{
    return m_text;
}

// Convert some HTML entities into characters
std::string TextElementProperties::_ProcessHTMLEntities(const std::string& input)
{
    static const std::regex htmlEntities("&(amp|quot|lt|gt|nbsp);");

    if (std::regex_search(input, htmlEntities))
    {
        // this needs to be kept up to date with htmlEntities above
        // clang-format off
        static const std::vector<std::pair<std::regex, std::string>> replacements =
            {
                { std::regex("&quot;"), "\"" },
                { std::regex("&lt;"), "<" },
                { std::regex("&gt;"), ">" },
                { std::regex("&nbsp;"), " " },
                { std::regex("&amp;"), "&" } // amp must be last
            };
        // clang-format on

        // handle entities
        std::string output = input;

        for (const auto& replacement : replacements)
        {
            output = std::regex_replace(output, replacement.first, replacement.second);
        }

        return output;
    }
    else
    {
        return input;
    }
}

void TextElementProperties::SetText(const std::string& value)
{
    m_text = _ProcessHTMLEntities(value);
}

DateTimePreparser TextElementProperties::GetTextForDateParsing() const
{
    return DateTimePreparser(m_text);
}

std::optional<TextSize> TextElementProperties::GetTextSize() const
{
    return m_textSize;
}

void TextElementProperties::SetTextSize(const std::optional<TextSize> value)
{
    m_textSize = value;
}

std::optional<TextWeight> TextElementProperties::GetTextWeight() const
{
    return m_textWeight;
}

void TextElementProperties::SetTextWeight(const std::optional<TextWeight> value)
{
    m_textWeight = value;
}

std::optional<FontType> TextElementProperties::GetFontType() const
{
    return m_fontType;
}

void TextElementProperties::SetFontType(const std::optional<FontType> value)
{
    m_fontType = value;
}

std::optional<ForegroundColor> TextElementProperties::GetTextColor() const
{
    return m_textColor;
}

void TextElementProperties::SetTextColor(const std::optional<ForegroundColor> value)
{
    m_textColor = value;
}

std::optional<bool> TextElementProperties::GetIsSubtle() const
{
    return m_isSubtle;
}

void TextElementProperties::SetIsSubtle(const std::optional<bool> value)
{
    m_isSubtle = value;
}

const std::string& TextElementProperties::GetLanguage() const
{
    return m_language;
}

void TextElementProperties::SetLanguage(const std::string& value)
{
    m_language = value;
}

void TextElementProperties::Deserialize(ParseContext& context, const Json::Value& json)
{
    SetText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text, false));
    if (GetText().empty())
    {
        context.warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
            WarningStatusCode::RequiredPropertyMissing, "required property, \"text\", is either empty or missing"));
    }

    SetTextSize(ParseUtil::GetOptionalEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, TextSizeFromString));
    SetTextColor(ParseUtil::GetOptionalEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, ForegroundColorFromString));
    SetTextWeight(ParseUtil::GetOptionalEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeightFromString));
    SetFontType(ParseUtil::GetOptionalEnumValue<FontType>(json, AdaptiveCardSchemaKey::FontType, FontTypeFromString));
    SetIsSubtle(ParseUtil::GetOptionalBool(json, AdaptiveCardSchemaKey::IsSubtle));
    SetLanguage(context.GetLanguage());
}

void TextElementProperties::PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties)
{
    knownProperties.insert(
        {AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TextWeight),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontType),
         AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle)});
}
