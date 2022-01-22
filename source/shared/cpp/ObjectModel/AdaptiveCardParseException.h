// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveCards
{
class AdaptiveCardParseException : public std::exception
{
public:
    AdaptiveCardParseException(AdaptiveCards::ErrorStatusCode statusCode, const std::string& message);

    virtual const char* what() const throw();
    AdaptiveCards::ErrorStatusCode GetStatusCode() const;
    const std::string& GetReason() const;

private:
    const AdaptiveCards::ErrorStatusCode m_statusCode;
    const std::string m_message;
};

} // namespace AdaptiveCards
