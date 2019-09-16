// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardParseWarning.h"

using namespace AdaptiveSharedNamespace;

AdaptiveCardParseWarning::AdaptiveCardParseWarning(const WarningStatusCode statusCode, const std::string& message) :
    m_statusCode(statusCode), m_message(message)
{
}

WarningStatusCode AdaptiveCardParseWarning::GetStatusCode() const
{
    return m_statusCode;
}

const std::string& AdaptiveCardParseWarning::GetReason() const
{
    return m_message;
}
