// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Fact.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Fact::Fact()
{
}

Fact::Fact(std::string const& title, std::string const& value) : m_title(title), m_value(value)
{
}

std::shared_ptr<Fact> Fact::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::string title = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title, false);
    std::string value = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value, false);

    if (title.empty() && value.empty())
    {
        context.warnings.emplace_back(
            std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::RequiredPropertyMissing,
                                                       "non-empty string has to be given for either title or value, none given"));
    }
    auto fact = std::make_shared<Fact>(title, value);
    fact->SetLanguage(context.GetLanguage());

    return fact;
}

std::shared_ptr<Fact> Fact::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return Fact::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::string Fact::Serialize()
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value Fact::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = GetTitle();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = GetValue();

    return root;
}

std::string Fact::GetTitle() const
{
    return m_title;
}

void Fact::SetTitle(const std::string& value)
{
    m_title = value;
}

std::string Fact::GetValue() const
{
    return m_value;
}

void Fact::SetValue(const std::string& value)
{
    m_value = value;
}

DateTimePreparser Fact::GetTitleForDateParsing() const
{
    return DateTimePreparser(m_title);
}

DateTimePreparser Fact::GetValueForDateParsing() const
{
    return DateTimePreparser(m_value);
}

const std::string& Fact::GetLanguage() const
{
    return m_language;
}

void Fact::SetLanguage(const std::string& value)
{
    m_language = value;
}
