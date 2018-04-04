#include "pch.h"
#include "AdaptiveCardParseException.h"

using namespace AdaptiveSharedNamespace;

AdaptiveCardParseException::AdaptiveCardParseException(const ErrorStatusCode statusCode, const std::string & message) : m_statusCode(statusCode), m_message(message)
{
}

AdaptiveCardParseException::~AdaptiveCardParseException()
{
}

const char* AdaptiveCardParseException::what() const throw()
{
    return m_message.c_str();
}

const ErrorStatusCode AdaptiveCardParseException::GetStatusCode() const
{
    return m_statusCode;
}

const std::string& AdaptiveCardParseException::GetReason() const
{
    return m_message;
}