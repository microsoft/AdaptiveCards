#pragma once

#include "pch.h"

namespace AdaptiveCards
{

class ACParseException : public std::exception
{
public:
    ACParseException(const std::string& message);
    ~ACParseException();

    virtual const char* what() const throw();

private:
    const std::string m_message;
};

}
