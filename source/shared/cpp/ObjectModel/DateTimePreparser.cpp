// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#if defined(__ANDROID__) || (__APPLE__) || (__linux__)
#define LOCALTIME(X, Y) (nullptr == localtime_r(Y, X))
#else
#define LOCALTIME(X, Y) localtime_s(X, Y)
#endif

#include "DateTimePreparsedToken.h"

#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include <iomanip>

using namespace AdaptiveSharedNamespace;

DateTimePreparser::DateTimePreparser() : m_hasDateTokens(false)
{
}

DateTimePreparser::DateTimePreparser(std::string const& in) : m_hasDateTokens(false)
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

void DateTimePreparser::AddTextToken(const std::string& text, DateTimePreparsedTokenFormat format)
{
    if (!text.empty())
    {
        m_textTokenCollection.emplace_back(std::make_shared<DateTimePreparsedToken>(text, format));
    }
}

void DateTimePreparser::AddDateToken(const std::string& text, struct tm& date, DateTimePreparsedTokenFormat format)
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

bool DateTimePreparser::IsValidDate(const int year, const int month, const int day)
{
    if (month <= 12 && day <= 31)
    {
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            return day <= 30;
        }
        else if (month == 2)
        {
            /// check for leap year
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            {
                return day <= 29;
            }

            return day <= 28;
        }
        return true;
    }
    return false;
}

bool DateTimePreparser::IsValidTime(const int hours, const int minutes, const int seconds)
{
    return (hours <= 24 && minutes <= 60 && seconds <= 60);
}

bool DateTimePreparser::IsValidTimeAndDate(const struct tm& parsedTm, const int hours, const int minutes)
{
    return IsValidDate(parsedTm.tm_year, parsedTm.tm_mon, parsedTm.tm_mday) &&
        IsValidTime(parsedTm.tm_hour, parsedTm.tm_min, parsedTm.tm_sec) && IsValidTime(hours, minutes, 0);
}

constexpr time_t IntToTimeT(int timeToConvert)
{
#pragma warning(push)
#pragma warning(disable : 26472)
    // disable warning about using static_cast since we need to hard cast up.
    return static_cast<time_t>(timeToConvert);
#pragma warning(pop)
}

void DateTimePreparser::ParseDateTime(const std::string& in)
{
    if (in.find("{{") != std::string::npos)
    {
        static const std::regex pattern(
            "\\{\\{((DATE)|(TIME))\\((\\d{4})-{1}(\\d{2})-{1}(\\d{2})T(\\d{2}):{1}(\\d{2}):{1}(\\d{2})(Z|(([+-])(\\d{2}):{1}(\\d{2})))((((, ?SHORT)|(, ?LONG))|(, ?COMPACT))|)\\)\\}\\}");
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
            struct tm parsedTm
            {
            };
            std::vector<int*> addrs = {
                &parsedTm.tm_year, &parsedTm.tm_mon, &parsedTm.tm_mday, &parsedTm.tm_hour, &parsedTm.tm_min, &parsedTm.tm_sec, &hours, &minutes};

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
#pragma warning(disable : 26485)
                char tzOffsetBuff[6]{};
                // gets local time zone offset
                strftime(tzOffsetBuff, 6, "%z", &parsedTm);
                std::string localTimeZoneOffsetStr(tzOffsetBuff);
                const time_t nTzOffset = IntToTimeT(std::stoi(localTimeZoneOffsetStr));
                offset += ((nTzOffset / 100) * 3600 + (nTzOffset % 100) * 60);
                // add offset to utc
                utc += offset;
                struct tm result
                {
                };
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
                        case 'C':
                        default:
                            AddDateToken(matches[0].str(), result, DateTimePreparsedTokenFormat::DateCompact);
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
    else
    {
        AddTextToken(in, DateTimePreparsedTokenFormat::RegularString);
    }
}

// Parses a time of the form HH:MM
bool DateTimePreparser::TryParseSimpleTime(const std::string& string, unsigned int& hours, unsigned int& minutes)
{
    std::smatch subMatches;
    static const std::regex timeMatch(R"regex(^(\d{2}):(\d{2})$)regex");
    if (std::regex_match(string, subMatches, timeMatch))
    {
        if (subMatches[1].matched && subMatches[2].matched)
        {
            unsigned int parsedHours = std::stoul(subMatches[1]);
            unsigned int parsedMinutes = std::stoul(subMatches[2]);

            if (IsValidTime(parsedHours, parsedMinutes, 0))
            {
                hours = parsedHours;
                minutes = parsedMinutes;
                return true;
            }
        }
    }
    return false;
}

// Parses a date of the form YYYY-MM-DD
bool DateTimePreparser::TryParseSimpleDate(const std::string& string, unsigned int& year, unsigned int& month, unsigned int& day)
{
    std::smatch subMatches;
    static const std::regex dateMatch(R"regex(^(\d{4})-(\d{2})-(\d{2})$)regex");
    if (std::regex_match(string, subMatches, dateMatch))
    {
        if (subMatches[1].matched && subMatches[2].matched && subMatches[3].matched)
        {
            unsigned int parsedYear = std::stoul(subMatches[1]);
            unsigned int parsedMonth = std::stoul(subMatches[2]);
            unsigned int parsedDay = std::stoul(subMatches[3]);

            if (IsValidDate(parsedYear, parsedMonth, parsedDay))
            {
                year = parsedYear;
                month = parsedMonth;
                day = parsedDay;
                return true;
            }
        }
    }
    return false;
}
