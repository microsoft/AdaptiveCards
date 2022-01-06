// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"

namespace AdaptiveCards
{
class Fact
{
public:
    Fact();
    Fact(std::string const& title, std::string const& value);

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::string GetTitle() const;
    void SetTitle(const std::string& value);

    std::string GetValue() const;
    void SetValue(const std::string& value);
    DateTimePreparser GetTitleForDateParsing() const;
    DateTimePreparser GetValueForDateParsing() const;

    void SetLanguage(const std::string& value);
    const std::string& GetLanguage() const;

    static std::shared_ptr<Fact> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<Fact> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::string m_title;
    std::string m_value;
    std::string m_language;
};
} // namespace AdaptiveCards
