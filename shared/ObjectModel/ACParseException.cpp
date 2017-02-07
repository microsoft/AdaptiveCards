#include "ACParseException.h"

using namespace AdaptiveCards;

ACParseException::ACParseException(const std::string & message) : m_message(message)
{
}

ACParseException::~ACParseException()
{
}

const char * ACParseException::what() const throw()
{
    return m_message.c_str();
}
