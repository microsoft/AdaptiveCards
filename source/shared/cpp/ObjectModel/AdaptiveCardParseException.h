#pragma once

#include "pch.h"
#include "enums.h"

namespace AdaptiveCards
{

class AdaptiveCardParseException : public std::exception
{
public:
    AdaptiveCardParseException(const AdaptiveCards::ErrorStatusCode statusCode, const std::string& message);
    ~AdaptiveCardParseException();

    virtual const char* what() const throw();
    const AdaptiveCards::ErrorStatusCode GetStatusCode() const;
    const std::string& GetMessage() const;

private:
    const AdaptiveCards::ErrorStatusCode m_statusCode;
    const std::string m_message;
};

}
