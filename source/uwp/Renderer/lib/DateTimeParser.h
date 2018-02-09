#pragma once
#include "TextBlockText.h"

#include <codecvt>
#include <string>

namespace AdaptiveCards
{
    class DateTimeParser
    {
    public:
        DateTimeParser(const std::string& language);
        std::string GenerateString(TextBlockText text);

    private:
        std::string WstringToString(const std::wstring& in) const;
        std::wstring StringToWstring(const std::string& in) const;

        std::locale m_language;
    };
}