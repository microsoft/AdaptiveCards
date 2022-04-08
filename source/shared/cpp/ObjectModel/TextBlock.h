// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include "TextElementProperties.h"

namespace AdaptiveCards
{
class TextBlockParser;

class TextBlock : public BaseCardElement
{
    friend TextBlockParser;

public:
    TextBlock();
    TextBlock(const TextBlock&) = default;
    TextBlock(TextBlock&&) = default;
    TextBlock& operator=(const TextBlock&) = default;
    TextBlock& operator=(TextBlock&&) = default;
    ~TextBlock() = default;

    Json::Value SerializeToJsonValue() const override;

    std::string GetText() const;
    void SetText(const std::string& value);
    DateTimePreparser GetTextForDateParsing() const;

    std::optional<TextStyle> GetStyle() const;
    void SetStyle(const std::optional<TextStyle> value);

    std::optional<TextSize> GetTextSize() const;
    void SetTextSize(const std::optional<TextSize> value);

    std::optional<TextWeight> GetTextWeight() const;
    void SetTextWeight(const std::optional<TextWeight> value);

    std::optional<FontType> GetFontType() const;
    void SetFontType(const std::optional<FontType> value);

    std::optional<ForegroundColor> GetTextColor() const;
    void SetTextColor(const std::optional<ForegroundColor> value);

    bool GetWrap() const;
    void SetWrap(const bool value);

    std::optional<bool> GetIsSubtle() const;
    void SetIsSubtle(const std::optional<bool> value);

    unsigned int GetMaxLines() const;
    void SetMaxLines(const unsigned int value);

    std::optional<HorizontalAlignment> GetHorizontalAlignment() const;
    void SetHorizontalAlignment(const std::optional<HorizontalAlignment> value);

    void SetLanguage(const std::string& value);
    const std::string& GetLanguage() const;

private:
    bool m_wrap;
    unsigned int m_maxLines;
    std::optional<HorizontalAlignment> m_hAlignment;
    std::optional<TextStyle> m_textStyle;
    std::shared_ptr<TextElementProperties> m_textElementProperties;
    void PopulateKnownPropertiesSet();
};

class TextBlockParser : public BaseCardElementParser
{
public:
    TextBlockParser() = default;
    TextBlockParser(const TextBlockParser&) = default;
    TextBlockParser(TextBlockParser&&) = default;
    TextBlockParser& operator=(const TextBlockParser&) = default;
    TextBlockParser& operator=(TextBlockParser&&) = default;
    virtual ~TextBlockParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
