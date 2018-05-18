#pragma once

#include "pch.h"
#include "AdaptiveCardParseWarning.h"

AdaptiveSharedNamespaceStart
    class AdaptiveCard;

    class ParseResult
    {
    public:
        ParseResult(
            std::shared_ptr<AdaptiveCard> adaptiveCard,
            std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings);

        std::shared_ptr<AdaptiveCard> GetAdaptiveCard() const;
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> GetWarnings() const;

    private:
        std::shared_ptr<AdaptiveCard> m_adaptiveCard;
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> m_warnings;
    };
AdaptiveSharedNamespaceEnd