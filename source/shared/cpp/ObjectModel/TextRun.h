// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ElementParserRegistration.h"
#include "Inline.h"
#include "RichTextElementProperties.h"

namespace AdaptiveSharedNamespace
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

        TextSize GetTextSize() const;
        void SetTextSize(const TextSize value);

        TextWeight GetTextWeight() const;
        void SetTextWeight(const TextWeight value);

        FontType GetFontType() const;
        void SetFontType(const FontType value);

        ForegroundColor GetTextColor() const;
        void SetTextColor(const ForegroundColor value);

        bool GetIsSubtle() const;
        void SetIsSubtle(const bool value);

        bool GetItalic() const;
        void SetItalic(const bool value);

        bool GetStrikethrough() const;
        void SetStrikethrough(const bool value);

        bool GetHighlight() const;
        void SetHighlight(const bool value);

        void SetLanguage(const std::string& value);
        std::string GetLanguage() const;

        bool GetUnderline() const;
        void SetUnderline(const bool value);

        std::shared_ptr<BaseActionElement> GetSelectAction() const;
        void SetSelectAction(const std::shared_ptr<BaseActionElement> action);

    protected:
        std::shared_ptr<RichTextElementProperties> m_textElementProperties;
        void PopulateKnownPropertiesSet();
        std::shared_ptr<BaseActionElement> m_selectAction;
        bool m_highlight;
    };
}
