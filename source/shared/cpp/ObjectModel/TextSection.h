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
        int GetDay() const;
        int GetMonth() const;
        int GetYear() const;
        int GetSecond() const;
        int GetMinute() const;
        int GetHour() const;

    private:
        std::vector<std::string> Split(const std::string& in, char delimiter) const;

        std::string m_text;
        std::string m_originalText;
        TextSectionFormat m_format;
    };
}