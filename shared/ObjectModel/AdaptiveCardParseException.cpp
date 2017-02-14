#include "AdaptiveCardParseException.h"

using namespace AdaptiveCards;

AdaptiveCardParseException::AdaptiveCardParseException(const std::string & message) : m_message(message)
{
}

AdaptiveCardParseException::~AdaptiveCardParseException()
{
}

const char * AdaptiveCardParseException::what() const throw()
{
    return m_message.c_str();
}
