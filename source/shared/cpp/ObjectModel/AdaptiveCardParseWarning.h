#pragma once

#include "pch.h"
#include "Enums.h"

AdaptiveSharedNamespaceStart

class AdaptiveCardParseWarning
{
public:
    AdaptiveCardParseWarning(AdaptiveSharedNamespace::WarningStatusCode statusCode, const std::string& message);
    ~AdaptiveCardParseWarning();

    AdaptiveSharedNamespace::WarningStatusCode GetStatusCode() const;
    const std::string& GetReason() const;

private:
    const AdaptiveSharedNamespace::WarningStatusCode m_statusCode;
    const std::string m_message;
};

AdaptiveSharedNamespaceEnd

