#pragma once
#include <string>
#include <vector>
#include "Enums.h"
#include "TextSection.h"
#include "TextSection.h"

namespace AdaptiveCards
{   
    class TextBlockText
    {
    public:
        TextBlockText();
        TextBlockText(std::string in);
        std::vector<TextSection> GetString() const;
        void AddTextSection(std::string text, TextSectionFormat format);
        void AddTextSection(std::string text, std::string originalText, TextSectionFormat format);
        std::string Concatenate();

    private:
        static bool IsValidTimeAndDate(const struct tm &parsedTm, int hours, int minutes);
        void ParseDateTime(std::string in);        

        std::vector<TextSection> m_fullString;
    };
}