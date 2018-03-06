#pragma once

#include "pch.h"
#include "Enums.h"

namespace AdaptiveCards
{

class AdaptiveCardParseWarning
{
public:
    AdaptiveCardParseWarning(const AdaptiveCards::WarningStatusCode statusCode, const std::string& message);
    ~AdaptiveCardParseWarning();

    const AdaptiveCards::WarningStatusCode GetStatusCode() const;
    const std::string& GetReason() const;

private:
    const AdaptiveCards::WarningStatusCode m_statusCode;
    const std::string m_message;
};

}
