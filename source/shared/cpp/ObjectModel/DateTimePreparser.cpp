#include "pch.h"

#if defined(__ANDROID__) || (__APPLE__) || (__linux__)
#define LOCALTIME(X,Y) (nullptr == localtime_r(Y, X))
#else
#define LOCALTIME(X,Y) localtime_s(X,Y)
#endif

#include "DateTimePreparsedToken.h"

#include "BaseCardElement.h"
#include "Enums.h"
#include <time.h>
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include <iomanip>
#include <iostream>
#include <codecvt>

using namespace AdaptiveSharedNamespace;

DateTimePreparser::DateTimePreparser() : m_hasDateTokens(false)
{
}

DateTimePreparser::DateTimePreparser(std::string const &in) : m_hasDateTokens(false)
{
    ParseDateTime(in);
}

std::vector<std::shared_ptr<DateTimePreparsedToken>> DateTimePreparser::GetTextTokens() const
{
    return m_textTokenCollection;
}

bool DateTimePreparser::HasDateTokens() const
{
    return m_hasDateTokens;
}

void DateTimePreparser::AddTextToken(std::string const &text, DateTimePreparsedTokenFormat format)
{
    if (!text.empty())
    {
        m_textTokenCollection.emplace_back(std::make_shared<DateTimePreparsedToken>(text, format));
    }
}

void DateTimePreparser::AddDateToken(std::string const &text, struct tm date, DateTimePreparsedTokenFormat format)
{
    m_textTokenCollection.emplace_back(std::make_shared<DateTimePreparsedToken>(text, date, format));
    m_hasDateTokens = true;
}

std::string DateTimePreparser::Concatenate() const
{
    std::string formedString;
    for (const auto& piece : m_textTokenCollection)
    {
        formedString += piece->GetText();
    }
    return formedString;
}

bool DateTimePreparser::IsValidTimeAndDate(const struct tm &parsedTm, const int hours, const int minutes)
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

constexpr time_t IntToTimeT(int timeToConvert)
{
#pragma warning(push)
#pragma warning(disable: 26472)
    // disable warning about using static_cast since we need to hard cast up.
    return static_cast<time_t>(timeToConvert);
#pragma warning(pop)
}

void DateTimePreparser::ParseDateTime(std::string const &in)
{
    std::vector<DateTimePreparsedToken> sections;

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
        int formatStyle{};
        // Date is matched
        const bool isDate = matches[IsDate].matched;
        int hours{}, minutes{};
        struct tm parsedTm{};
        std::vector<int*> addrs = { &parsedTm.tm_year, &parsedTm.tm_mon,
            &parsedTm.tm_mday, &parsedTm.tm_hour, &parsedTm.tm_min,
            &parsedTm.tm_sec, &hours, &minutes };

        if (matches[Style].matched)
        {
            // match for long/short/compact
            bool formatHasSpace = matches[Format].str().at(1) == ' ';
            const int formatStartIndex = formatHasSpace ? 2 : 1;
            formatStyle = matches[Format].str().at(formatStartIndex);
        }

        AddTextToken(matches.prefix().str(), DateTimePreparsedTokenFormat::RegularString);

        if (!isDate && formatStyle)
        {
            AddTextToken(matches[0].str(), DateTimePreparsedTokenFormat::RegularString);
            text = matches.suffix().str();
            continue;
        }

        for (unsigned int idx = 0; idx < indexer.size(); idx++)
        {
            if (matches[indexer.at(idx)].matched)
            {
                // get indexes for time attributes to index into corresponding matches
                // and convert it to string
                *(addrs.at(idx)) = stoi(matches[indexer.at(idx)]);
            }
        }

        // check for date and time validation
        if (IsValidTimeAndDate(parsedTm, hours, minutes))
        {
            time_t offset{};
            // maches offset sign,
            // Z == UTC,
            // + == time added from UTC
            // - == time subtracted from UTC
            if (matches[TimeZone].matched)
            {
                // converts to seconds
                hours *= 3600;
                minutes *= 60;
                offset = IntToTimeT(hours) + IntToTimeT(minutes);

                wchar_t zone = matches[TimeZone].str().at(0);
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
                AddTextToken(matches[0], DateTimePreparsedTokenFormat::RegularString);
            }

// Disable "array to pointer decay" check for tzOffsetBuff since we can't change strftime's signature
#pragma warning(push)
#pragma warning(disable: 26485)
            char tzOffsetBuff[6]{};
            // gets local time zone offset
            strftime(tzOffsetBuff, 6, "%z", &parsedTm);
            std::string localTimeZoneOffsetStr(tzOffsetBuff);
            const time_t nTzOffset = IntToTimeT(std::stoi(localTimeZoneOffsetStr));
            offset += ((nTzOffset / 100) * 3600 + (nTzOffset % 100) * 60);
            // add offset to utc
            utc += offset;
            struct tm result{};
#pragma warning(pop)

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
                    switch (formatStyle)
                    {
                        // SHORT Style
                        case 'S':
                            AddDateToken(matches[0].str(), result, DateTimePreparsedTokenFormat::DateShort);
                            break;
                        // LONG Style
                        case 'L':
                            AddDateToken(matches[0].str(), result, DateTimePreparsedTokenFormat::DateLong);
                            break;
                        // COMPACT or DEFAULT Style
                        case 'C': default:
                            AddDateToken(matches[0].str(), result , DateTimePreparsedTokenFormat::DateCompact);
                            break;
                    }
                }
                else
                {
                    std::ostringstream parsedTime;
                    parsedTime << std::put_time(&result, "%I:%M %p");
                    AddTextToken(parsedTime.str(), DateTimePreparsedTokenFormat::RegularString);
                }
            }
        }
        else
        {
            AddTextToken(matches[0].str(), DateTimePreparsedTokenFormat::RegularString);
        }

        text = matches.suffix().str();
    }

    AddTextToken(text, DateTimePreparsedTokenFormat::RegularString);
}
