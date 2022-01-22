// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveCards
{
class AdaptiveCardParseWarning
{
public:
    AdaptiveCardParseWarning(AdaptiveCards::WarningStatusCode statusCode, const std::string& message);

    AdaptiveCards::WarningStatusCode GetStatusCode() const;
    const std::string& GetReason() const;

private:
    const AdaptiveCards::WarningStatusCode m_statusCode;
    const std::string m_message;
};

} // namespace AdaptiveCards
