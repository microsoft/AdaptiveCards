// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveCards
{
    class AdaptiveCard;
    class AdaptiveCardParseWarning;

    class ParseResult
    {
    public:
        ParseResult(std::shared_ptr<AdaptiveCard> adaptiveCard, std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings);

        std::shared_ptr<AdaptiveCard> GetAdaptiveCard() const;
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> GetWarnings() const;

    private:
        std::shared_ptr<AdaptiveCard> m_adaptiveCard;
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>> m_warnings;
    };
}
