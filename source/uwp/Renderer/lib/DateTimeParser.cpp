#include "pch.h"
#include "DateTimeParser.h"
#include "Util.h"
#include <iomanip>
#include <sstream>

AdaptiveNamespaceStart

DateTimeParser::DateTimeParser(const std::string& language)
{
    m_languageString = language;
}

std::string DateTimeParser::GenerateString(DateTimePreparser text)
{
    std::wostringstream parsedostr;

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
        struct tm result{};
        result.tm_mday = textSection->GetDay();
        result.tm_mon = textSection->GetMonth();
        result.tm_year = textSection->GetYear() >= 1900 ? textSection->GetYear() - 1900 : 0;

        DateTimePreparsedTokenFormat format = textSection->GetFormat();
        // using the put_time function the 3 formats are locale dependent
        switch (format)
        {
            case DateTimePreparsedTokenFormat::DateCompact:
                parsedostr << std::put_time(&result, L"%Ex");
                break;
            case DateTimePreparsedTokenFormat::DateShort:
                mktime(&result);
                parsedostr << std::put_time(&result, L"%a, %b %e, %Y");
                break;
            case DateTimePreparsedTokenFormat::DateLong:
                mktime(&result);
                parsedostr << std::put_time(&result, L"%A, %B %e, %Y");
                break;
            case DateTimePreparsedTokenFormat::RegularString:
            default:
                parsedostr << StringToWstring(textSection->GetText());
                break;
        }
    }

    return WstringToString(parsedostr.str());
}

AdaptiveNamespaceEnd