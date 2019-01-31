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

    private:
        void AddTextToken(std::string const& text, DateTimePreparsedTokenFormat format);
        void AddDateToken(std::string const& text, struct tm date, DateTimePreparsedTokenFormat format);
        std::string Concatenate() const;
        static bool IsValidTimeAndDate(const struct tm& parsedTm, const int hours, const int minutes);
        void ParseDateTime(std::string const& in);

        std::vector<std::shared_ptr<DateTimePreparsedToken>> m_textTokenCollection;
        bool m_hasDateTokens;
    };
}
