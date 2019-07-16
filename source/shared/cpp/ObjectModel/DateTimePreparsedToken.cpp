// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "DateTimePreparsedToken.h"

using namespace AdaptiveSharedNamespace;

DateTimePreparsedToken::DateTimePreparsedToken() :
    m_text(""), m_date{}, m_format(DateTimePreparsedTokenFormat::RegularString)
{
}

DateTimePreparsedToken::DateTimePreparsedToken(std::string const& text, DateTimePreparsedTokenFormat format) :
    m_text(text), m_date{}, m_format(format)
{
}

DateTimePreparsedToken::DateTimePreparsedToken(std::string const& text, struct tm date, DateTimePreparsedTokenFormat format) :
    m_text(text), m_date(date), m_format(format)
{
}

std::string DateTimePreparsedToken::GetText() const
{
    return m_text;
}

DateTimePreparsedTokenFormat DateTimePreparsedToken::GetFormat() const
{
    return m_format;
}

int DateTimePreparsedToken::GetDay() const
{
    return m_date.tm_mday;
}

int DateTimePreparsedToken::GetMonth() const
{
    return m_date.tm_mon;
}

int DateTimePreparsedToken::GetYear() const
{
    return m_date.tm_year + 1900;
}
