#pragma once
#include <string>
#include <vector>
#include "Enums.h"
#include "DateTimePreparsedToken.h"

AdaptiveSharedNamespaceStart   
    // Still have to rename this thing
    class DateTimePreparser
    {
    public:
        DateTimePreparser();
        DateTimePreparser(std::string in);
        std::vector<std::shared_ptr<DateTimePreparsedToken>> GetTextTokens() const;
        bool HasDateTokens();

    private:
        void AddTextToken(std::string text, DateTimePreparsedTokenFormat format);
        void AddDateToken(std::string text, struct tm date, DateTimePreparsedTokenFormat format);
        std::string Concatenate();
        static bool IsValidTimeAndDate(const struct tm &parsedTm, int hours, int minutes);
        void ParseDateTime(std::string in);        

        std::vector<std::shared_ptr<DateTimePreparsedToken>> m_textTokenCollection;
        bool m_hasDateTokens;
    };
AdaptiveSharedNamespaceEnd