#pragma once

#include "pch.h"
#include "Enums.h"

AdaptiveSharedNamespaceStart

class AdaptiveCardParseException : public std::exception
{
public:
    AdaptiveCardParseException(const AdaptiveSharedNamespace::ErrorStatusCode statusCode, const std::string& message);
    ~AdaptiveCardParseException();

    virtual const char* what() const throw();
    const AdaptiveSharedNamespace::ErrorStatusCode GetStatusCode() const;
    const std::string& GetReason() const;

private:
    const AdaptiveSharedNamespace::ErrorStatusCode m_statusCode;
    const std::string m_message;
};

AdaptiveSharedNamespaceEnd
