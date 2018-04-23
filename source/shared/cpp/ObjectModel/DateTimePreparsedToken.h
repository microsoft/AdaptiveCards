#pragma once
#include <string>
#include <vector>
#include "Enums.h"

AdaptiveSharedNamespaceStart
    class DateTimePreparsedToken
    {
    public:
        DateTimePreparsedToken();
        DateTimePreparsedToken(std::string text, DateTimePreparsedTokenFormat format);
        DateTimePreparsedToken(std::string text, struct tm date, DateTimePreparsedTokenFormat format);

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
AdaptiveSharedNamespaceEnd