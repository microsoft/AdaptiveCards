#pragma once

#include "pch.h"

namespace AdaptiveCards
{

class AdaptiveCardParseException : public std::exception
{
public:
    AdaptiveCardParseException(const std::string& message);
    ~AdaptiveCardParseException();

    virtual const char* what() const throw();

private:
    const std::string m_message;
};

}
