// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardParseException.h"

using namespace AdaptiveSharedNamespace;

AdaptiveCardParseException::AdaptiveCardParseException(ErrorStatusCode statusCode, const std::string& message) :
    m_statusCode(statusCode), m_message(message)
{
}

#pragma warning(push)
#pragma warning(disable : 26433)
const char* AdaptiveCardParseException::what() const throw()
{
    return m_message.c_str();
}
#pragma warning(pop)

ErrorStatusCode AdaptiveCardParseException::GetStatusCode() const
{
    return m_statusCode;
}

const std::string& AdaptiveCardParseException::GetReason() const
{
    return m_message;
}
