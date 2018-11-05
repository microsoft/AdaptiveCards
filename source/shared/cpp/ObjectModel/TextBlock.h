#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include <time.h>
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"

namespace AdaptiveSharedNamespace
{
    class TextBlock : public BaseCardElement
    {
    public:
        TextBlock();

        Json::Value SerializeToJsonValue() const override;

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

        bool GetWrap() const;
        void SetWrap(const bool value);

        bool GetIsSubtle() const;
        void SetIsSubtle(const bool value);

        unsigned int GetMaxLines() const;
        void SetMaxLines(const unsigned int value);

        HorizontalAlignment GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const HorizontalAlignment value);

        void SetLanguage(const std::string& value);
        std::string GetLanguage() const;

    private:
        std::string m_text;
        TextSize m_textSize;
        TextWeight m_textWeight;
        FontStyle m_fontStyle;
        ForegroundColor m_textColor;
        bool m_isSubtle;
        bool m_wrap;
        unsigned int m_maxLines;
        HorizontalAlignment m_hAlignment;
        void PopulateKnownPropertiesSet() override;
        std::string m_language;
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

        std::shared_ptr<BaseCardElement> Deserialize(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                     std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                     std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                     const Json::Value& root) override;

        std::shared_ptr<BaseCardElement> DeserializeFromString(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                               std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                               std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                               const std::string& jsonString);
    };
}
