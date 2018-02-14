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
        // Date format should be: MM/DD/YYYY
        int GetDay() const;
        int GetMonth() const;
        int GetYear() const;

    private:
        std::vector<std::string> Split(const std::string& in, char delimiter) const;
        int GetDateSection(int position) const;

        std::string m_text;
        std::string m_originalText;
        TextSectionFormat m_format;
        const char dateDelimiter = '/';
    };
}