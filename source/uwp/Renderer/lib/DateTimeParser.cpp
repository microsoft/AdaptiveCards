// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "DateTimeParser.h"
#include "Util.h"
#include <iomanip>
#include <sstream>

namespace AdaptiveNamespace
{
    DateTimeParser::DateTimeParser(const std::string& language) { m_languageString = language; }

    std::string DateTimeParser::GenerateString(const DateTimePreparser& text)
    {
        std::ostringstream parsedostr;

        if (text.HasDateTokens())
        {
            std::locale language;
            try
            {
                language = std::locale(m_languageString.c_str());
            }
            catch (...)
            {
                language = std::locale("");
            }
            parsedostr.imbue(language);
        }

        for (const auto& textSection : text.GetTextTokens())
        {
            std::tm result = {};

            result.tm_mday = textSection->GetDay();
            result.tm_mon = textSection->GetMonth();
            result.tm_year = textSection->GetYear() >= 1900 ? textSection->GetYear() - 1900 : 0;

            // using the put_time function the 3 formats are locale dependent
            switch (textSection->GetFormat())
            {
            case DateTimePreparsedTokenFormat::DateCompact:
                parsedostr << std::put_time(&result, "%Ex");
                break;
            case DateTimePreparsedTokenFormat::DateShort:
                mktime(&result);
                parsedostr << std::put_time(&result, "%a, %b %e, %Y");
                break;
            case DateTimePreparsedTokenFormat::DateLong:
                mktime(&result);
                parsedostr << std::put_time(&result, "%A, %B %e, %Y");
                break;
            case DateTimePreparsedTokenFormat::RegularString:
            default:
                parsedostr << textSection->GetText();
                break;
            }
        }

        return parsedostr.str();
    }

}
