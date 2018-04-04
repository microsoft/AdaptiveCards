#pragma once
#include "DateTimePreparser.h"

#include <codecvt>
#include <string>

AdaptiveNamespaceStart
    class DateTimeParser
    {
    public:
        DateTimeParser(const std::string& language);
        std::string GenerateString(DateTimePreparser text);

    private:
        std::locale m_language;
    };
AdaptiveNamespaceEnd