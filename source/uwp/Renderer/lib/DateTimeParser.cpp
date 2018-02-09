#include "DateTimeParser.h"
#include <iomanip>
#include <sstream>

using namespace AdaptiveCards;

DateTimeParser::DateTimeParser(const std::string& language)
{
    try
    {
        m_language = std::locale(language.c_str());
    }
    catch (...)
    {
    }
}

std::string DateTimeParser::GenerateString(TextBlockText text)
{
    std::wostringstream parsedostr;

    for (const auto& textSection : text.GetString())
    {
        struct tm result{};
        result.tm_hour = textSection.GetHour();
        result.tm_min = textSection.GetMinute();
        result.tm_sec = textSection.GetSecond();
        result.tm_mday = textSection.GetDay();
        result.tm_mon = textSection.GetMonth();
        result.tm_year = textSection.GetYear() - 1900;

        switch (textSection.GetFormat())
        {
            case TextSectionFormat::Time:
                parsedostr << std::put_time(&result, L"%I:%M %p");
                break;
            case TextSectionFormat::DateCompact:
                parsedostr << std::put_time(&result, L"%Ex");
                break;
            case TextSectionFormat::DateShort:
                mktime(&result);
                parsedostr.imbue(m_language);
                parsedostr << std::put_time(&result, L"%a, %b %e, %Y");
                break;
            case TextSectionFormat::DateLong:
                mktime(&result);
                parsedostr.imbue(m_language);
                parsedostr << std::put_time(&result, L"%A, %B %e, %Y");
                break;
            case TextSectionFormat::RegularString:
            default:
                parsedostr << StringToWstring(textSection.GetText());
                break;
        }
    }

    return WstringToString(parsedostr.str());
}

std::wstring DateTimeParser::StringToWstring(const std::string& in) const
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utfConverter;
    return utfConverter.from_bytes(in);
}

std::string DateTimeParser::WstringToString(const std::wstring& input) const
{
    if (sizeof(wchar_t) == 2)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utfConverter;
        return utfConverter.to_bytes(input);
    }
    else
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utfConverter;
        return utfConverter.to_bytes(input);
    }
}