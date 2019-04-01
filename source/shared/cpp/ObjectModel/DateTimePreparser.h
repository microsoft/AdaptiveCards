#pragma once

#include "pch.h"
#include "DateTimePreparsedToken.h"

namespace AdaptiveSharedNamespace
{
    class DateTimePreparser
    {
    public:
        DateTimePreparser();
        DateTimePreparser(std::string const& in);
        std::vector<std::shared_ptr<DateTimePreparsedToken>> GetTextTokens() const;
        bool HasDateTokens() const;
        static bool TryParseSimpleTime(std::string string, unsigned int* hours, unsigned int* minutes);
        static bool TryParseSimpleDate(std::string string, unsigned int* year, unsigned int* month, unsigned int* day);

    private:
        void AddTextToken(std::string const& text, DateTimePreparsedTokenFormat format);
        void AddDateToken(std::string const& text, struct tm date, DateTimePreparsedTokenFormat format);
        std::string Concatenate() const;
        void ParseDateTime(std::string const& in);
        static bool IsValidDate(const int year, const int month, const int day);
        static bool IsValidTime(const int hours, const int minutes, const int seconds);
        static bool IsValidTimeAndDate(const struct tm& parsedTm, const int hours, const int minutes);

        std::vector<std::shared_ptr<DateTimePreparsedToken>> m_textTokenCollection;
        bool m_hasDateTokens;
    };
}
