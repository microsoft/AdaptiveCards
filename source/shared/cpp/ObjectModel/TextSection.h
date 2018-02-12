#pragma once
#include <string>
#include <vector>
#include "Enums.h"

namespace AdaptiveCards
{
    class TextSection
    {
    public:
        TextSection();
        TextSection(std::string text, TextSectionFormat format);
        TextSection(std::string text, std::string originalText, TextSectionFormat format);

        std::string GetText() const;
        std::string GetOriginalText() const;
        TextSectionFormat GetFormat() const;
        // Date format should be: MM/DD/YY
        int GetDay() const;
        int GetMonth() const;
        int GetYear() const;
        // Time format should be: HH/mm/ss
        int GetSecond() const;
        int GetMinute() const;
        int GetHour() const;

    private:
        std::vector<std::string> Split(const std::string& in, char delimiter) const;
        int GetDateSection(int position) const;
        int GetTimeSection(int position) const;

        std::string m_text;
        std::string m_originalText;
        TextSectionFormat m_format;
        const char dateDelimiter = '/';
        const char timeDelimiter = ':';
    };
}