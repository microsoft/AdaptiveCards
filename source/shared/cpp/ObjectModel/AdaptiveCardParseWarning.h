// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class AdaptiveCardParseWarning
    {
    public:
        AdaptiveCardParseWarning(AdaptiveSharedNamespace::WarningStatusCode statusCode, const std::string& message);

        AdaptiveSharedNamespace::WarningStatusCode GetStatusCode() const;
        const std::string& GetReason() const;

    private:
        const AdaptiveSharedNamespace::WarningStatusCode m_statusCode;
        const std::string m_message;
    };

}
