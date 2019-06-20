// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class DateTimePreparsedToken
    {
    public:
        DateTimePreparsedToken();
        DateTimePreparsedToken(std::string const& text, DateTimePreparsedTokenFormat format);
        DateTimePreparsedToken(std::string const& text, struct tm date, DateTimePreparsedTokenFormat format);

        std::string GetText() const;
        DateTimePreparsedTokenFormat GetFormat() const;
        // returns values 1-31
        int GetDay() const;
        // returns values 0-11
        int GetMonth() const;
        // return values 1900 onward
        int GetYear() const;

    private:
        std::string m_text;
        struct tm m_date;
        DateTimePreparsedTokenFormat m_format;
    };
}
