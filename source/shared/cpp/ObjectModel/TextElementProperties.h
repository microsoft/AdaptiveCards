// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include "HostConfig.h"

namespace AdaptiveCards
{
class TextElementProperties
{
public:
    TextElementProperties();
    TextElementProperties(const TextStyleConfig&, const std::string&, const std::string&);
    TextElementProperties(const TextElementProperties&) = default;
    TextElementProperties(TextElementProperties&&) = default;
    TextElementProperties& operator=(const TextElementProperties&) = default;
    TextElementProperties& operator=(TextElementProperties&&) = default;
    virtual ~TextElementProperties() = default;

    virtual Json::Value SerializeToJsonValue(Json::Value& root) const;

    std::string GetText() const;
    void SetText(const std::string& value);
    DateTimePreparser GetTextForDateParsing() const;

    std::optional<TextSize> GetTextSize() const;
    void SetTextSize(const std::optional<TextSize> value);

    std::optional<TextWeight> GetTextWeight() const;
    void SetTextWeight(const std::optional<TextWeight> value);

    std::optional<FontType> GetFontType() const;
    void SetFontType(const std::optional<FontType> value);

    std::optional<ForegroundColor> GetTextColor() const;
    void SetTextColor(const std::optional<ForegroundColor> value);

    std::optional<bool> GetIsSubtle() const;
    void SetIsSubtle(const std::optional<bool> value);

    void SetLanguage(const std::string& value);
    const std::string& GetLanguage() const;

    virtual void Deserialize(ParseContext& context, const Json::Value& root);
    virtual void PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties);

private:
    static std::string _ProcessHTMLEntities(const std::string& input);

    std::string m_text;
    std::optional<TextSize> m_textSize;
    std::optional<TextWeight> m_textWeight;
    std::optional<FontType> m_fontType;
    std::optional<ForegroundColor> m_textColor;
    std::optional<bool> m_isSubtle;
    std::string m_language;
};
} // namespace AdaptiveCards
