#if defined(__ANDROID__) || (__APPLE__) || (__linux__)
#define LOCALTIME(X,Y) (nullptr == localtime_r(Y, X))
#else
#define LOCALTIME(X,Y) localtime_s(X,Y)
#endif

#include "TextBlockText.h"

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include <time.h>
#include "ElementParserRegistration.h"
#include "TextBlockText.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>

using namespace AdaptiveCards;

TextBlockText::TextBlockText()
{
}

TextBlockText::TextBlockText(std::string in)
{
    ParseDateTime(in);
}

std::vector<std::shared_ptr<TextSection>> TextBlockText::GetString() const
{
    return m_fullString;
}

void TextBlockText::AddTextSection(std::string text, TextSectionFormat format)
{
    if (!text.empty())
    {
        m_fullString.emplace_back(std::make_shared<TextSection>(text, format));
    }
}

void TextBlockText::AddTextSection(std::string text, std::string originalText, TextSectionFormat format)
{
    m_fullString.emplace_back(std::make_shared<TextSection>(text, originalText, format));
}

std::string TextBlockText::Concatenate()
{
    std::string formedString;
    for (const auto& piece : m_fullString)
    {
        formedString += piece->GetOriginalText();
    }
    return formedString;
}

bool TextBlockText::IsValidTimeAndDate(const struct tm &parsedTm, int hours, int minutes)
{
    if (parsedTm.tm_mon <= 12 && parsedTm.tm_mday <= 31 && parsedTm.tm_hour <= 24 &&
        parsedTm.tm_min <= 60 && parsedTm.tm_sec <= 60 && hours <= 24 && minutes <= 60)
    {
        if (parsedTm.tm_mon == 4 || parsedTm.tm_mon == 6 || parsedTm.tm_mon == 9 || parsedTm.tm_mon == 11)
        {
            return parsedTm.tm_mday <= 30;
        }
        else if (parsedTm.tm_mon == 2)
        {
            /// check for leap year
            if ((parsedTm.tm_year % 4 == 0 && parsedTm.tm_year % 100 != 0) || parsedTm.tm_year % 400 == 0)
            {
                return parsedTm.tm_mday <= 29;
            }

            return parsedTm.tm_mday <= 28;
        }

        return true;
    }
    return false;
}

void TextBlockText::ParseDateTime(std::string in)
{
    const char dateDelimiter = '/';
    const char timeDelimiter = ':';

    std::vector<TextSection> sections;

    std::regex pattern("\\{\\{((DATE)|(TIME))\\((\\d{4})-{1}(\\d{2})-{1}(\\d{2})T(\\d{2}):{1}(\\d{2}):{1}(\\d{2})(Z|(([+-])(\\d{2}):{1}(\\d{2})))((((, ?SHORT)|(, ?LONG))|(, ?COMPACT))|)\\)\\}\\}");
    std::smatch matches;
    std::string text = in;
    enum MatchIndex
    {
        IsDate = 2,
        Year = 4,
        Month,
        Day,
        Hour,
        Min,
        Sec,
        TimeZone = 12,
        TZHr,
        TZMn,
        Format,
        Style,
    };
    std::vector<int> indexer = {Year, Month, Day, Hour, Min, Sec, TZHr, TZMn};

    while (std::regex_search(text, matches, pattern))
    {
        time_t offset{};
        int  formatStyle{};
        // Date is matched
        bool isDate = matches[IsDate].matched;
        int hours{}, minutes{};
        struct tm parsedTm{};
        int *addrs[] = {&parsedTm.tm_year, &parsedTm.tm_mon,
            &parsedTm.tm_mday, &parsedTm.tm_hour, &parsedTm.tm_min,
            &parsedTm.tm_sec, &hours, &minutes};

        if (matches[Style].matched)
        {
            // match for long/short/compact
            bool formatHasSpace = matches[Format].str()[1] == ' ';
            int formatStartIndex = formatHasSpace ? 2 : 1;
            formatStyle = matches[Format].str()[formatStartIndex];
        }

        AddTextSection(matches.prefix().str(), TextSectionFormat::RegularString);

        if (!isDate && formatStyle)
        {
            AddTextSection(matches[0].str(), TextSectionFormat::RegularString);
            text = matches.suffix().str();
            continue;
        }

        for (unsigned int idx = 0; idx < indexer.size(); idx++)
        {
            if (matches[indexer[idx]].matched)
            {
                // get indexes for time attributes to index into conrresponding matches
                // and covert it to string
                *addrs[idx] = stoi(matches[indexer[idx]]);
            }
        }

        // check for date and time validation
        if (IsValidTimeAndDate(parsedTm, hours, minutes))
        {
            // maches offset sign, 
            // Z == UTC, 
            // + == time added from UTC
            // - == time subtracted from UTC
            if (matches[TimeZone].matched)
            {
                // converts to seconds
                hours *= 3600;
                minutes *= 60;
                offset = hours + minutes;

                wchar_t zone = matches[TimeZone].str()[0];
                // time zone offset calculation 
                if (zone == '+')
                {
                    offset *= -1;
                }
            }

            // measured from year 1900
            parsedTm.tm_year -= 1900;
            parsedTm.tm_mon -= 1;

            time_t utc{};
            // converts to ticks in UTC
            utc = mktime(&parsedTm);
            if (utc == -1)
            {
                AddTextSection(matches[0], TextSectionFormat::RegularString);
            }

            wchar_t tzOffsetBuff[6]{};
            // gets local time zone offset
            wcsftime(tzOffsetBuff, 6, L"%z", &parsedTm);
            std::wstring localTimeZoneOffsetStr(tzOffsetBuff);
            int nTzOffset = std::stoi(localTimeZoneOffsetStr);
            offset += ((nTzOffset / 100) * 3600 + (nTzOffset % 100) * 60);
            // add offset to utc
            utc += offset;
            struct tm result{};

            // converts to local time from utc
            if (!LOCALTIME(&result, &utc))
            {
                // localtime() set dst, put_time adjusts time accordingly which is not what we want since 
                // we have already taken cared of it in our calculation
                if (result.tm_isdst == 1)
                {
                    result.tm_hour -= 1;
                }

                if (isDate)
                {
                    std::string plainDate = std::to_string(result.tm_mon) + dateDelimiter +
                        std::to_string(result.tm_mday) + dateDelimiter +
                        std::to_string(result.tm_year + 1900);

                    switch (formatStyle)
                    {
                        // SHORT Style
                        case 'S':
                            AddTextSection(plainDate, matches[0].str(), TextSectionFormat::DateShort);
                            break;
                        // LONG Style
                        case 'L':
                            AddTextSection(plainDate, matches[0].str(), TextSectionFormat::DateLong);
                            break;
                        // COMPACT or DEFAULT Style
                        case 'C': default:
                            AddTextSection(plainDate, matches[0].str(), TextSectionFormat::DateCompact);
                            break;
                    }
                }
                else
                {
                    std::ostringstream parsedTime;
                    parsedTime << std::put_time(&result, "%I:%M %p");
                    AddTextSection(parsedTime.str(), TextSectionFormat::RegularString);
                }
            }
        }
        else
        {
            AddTextSection(matches[0].str(), TextSectionFormat::RegularString);
        }
        
        text = matches.suffix().str();
    }

    AddTextSection(text, TextSectionFormat::RegularString);
}