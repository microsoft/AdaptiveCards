// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "DateTimePreparsedToken.h"

namespace AdaptiveSharedNamespace
{
    class DateTimePreparser
    {
    public:
        DateTimePreparser();
        DateTimePreparser(const std::string& in);
        std::vector<std::shared_ptr<DateTimePreparsedToken>> GetTextTokens() const;
        bool HasDateTokens() const;
        static bool TryParseSimpleTime(const std::string& string, unsigned int& hours, unsigned int& minutes);
        static bool TryParseSimpleDate(const std::string& string, unsigned int& year, unsigned int& month, unsigned int& day);

    private:
        void AddTextToken(const std::string& text, DateTimePreparsedTokenFormat format);
        void AddDateToken(const std::string& text, struct tm& date, DateTimePreparsedTokenFormat format);
        std::string Concatenate() const;
        void ParseDateTime(const std::string& in);
        static inline bool IsValidDate(const int year, const int month, const int day);
        static inline bool IsValidTime(const int hours, const int minutes, const int seconds);
        static inline bool IsValidTimeAndDate(const struct tm& parsedTm, const int hours, const int minutes);

        std::vector<std::shared_ptr<DateTimePreparsedToken>> m_textTokenCollection;
        bool m_hasDateTokens;
    };
}
