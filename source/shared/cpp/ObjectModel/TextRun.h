// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ElementParserRegistration.h"
#include "Inline.h"
#include "RichTextElementProperties.h"

namespace AdaptiveCards
{
class TextRun : public Inline
{
public:
    TextRun();
    TextRun(const TextRun&) = default;
    TextRun(TextRun&&) = default;
    TextRun& operator=(const TextRun&) = default;
    TextRun& operator=(TextRun&&) = default;
    ~TextRun() = default;

    Json::Value SerializeToJsonValue() const override;

    static std::shared_ptr<Inline> Deserialize(ParseContext& context, const Json::Value& root);

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

    bool GetItalic() const;
    void SetItalic(const bool value);

    bool GetStrikethrough() const;
    void SetStrikethrough(const bool value);

    bool GetHighlight() const;
    void SetHighlight(const bool value);

    void SetLanguage(const std::string& value);
    const std::string& GetLanguage() const;

    bool GetUnderline() const;
    void SetUnderline(const bool value);

    std::shared_ptr<BaseActionElement> GetSelectAction() const;
    void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

protected:
    std::shared_ptr<RichTextElementProperties> m_textElementProperties;
    std::shared_ptr<BaseActionElement> m_selectAction;
    bool m_highlight;

private:
    void PopulateKnownPropertiesSet();
};
} // namespace AdaptiveCards
