#pragma once
#include <string>
#include <vector>
#include "Enums.h"
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
        std::string Concatenate();

    private:
        std::u16string ToU16String(const std::string& in) const;
        std::u16string ToU16String(const std::wstring& in) const;

        std::wstring StringToWstring(const std::string& in) const;
        std::string WstringToString(const std::wstring& in) const;

        static bool IsValidTimeAndDate(const struct tm &parsedTm, int hours, int minutes);
        void ParseDateTime(std::string in);        

        std::vector<TextSection> m_fullString;
    };
}