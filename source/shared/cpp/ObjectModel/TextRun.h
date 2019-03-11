#pragma once

#include "pch.h"
#include "ElementParserRegistration.h"
#include "Inline.h"
#include "TextElementProperties.h"

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

        virtual Json::Value SerializeToJsonValue() const;

        static std::shared_ptr<Inline> Deserialize(ParseContext& context, const Json::Value& root);

        std::string GetText() const;
        void SetText(const std::string& value);
        DateTimePreparser GetTextForDateParsing() const;

        TextSize GetTextSize() const;
        void SetTextSize(const TextSize value);

        TextWeight GetTextWeight() const;
        void SetTextWeight(const TextWeight value);

        FontStyle GetFontStyle() const;
        void SetFontStyle(const FontStyle value);

        ForegroundColor GetTextColor() const;
        void SetTextColor(const ForegroundColor value);

        bool GetIsSubtle() const;
        void SetIsSubtle(const bool value);

        void SetLanguage(const std::string& value);
        std::string GetLanguage() const;

    protected:
        std::shared_ptr<TextElementProperties> m_textElementProperties;
        virtual void PopulateKnownPropertiesSet() override;
    };
}
