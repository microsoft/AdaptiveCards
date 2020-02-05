// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseResult.h"
#include "ParseResult.h"
#include "SharedAdaptiveCard.h"

using namespace AdaptiveSharedNamespace;

ParseResult::ParseResult(std::shared_ptr<AdaptiveCard> adaptiveCard, std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings) :
    m_adaptiveCard(adaptiveCard), m_warnings(warnings)
{
}

std::shared_ptr<AdaptiveCard> ParseResult::GetAdaptiveCard() const
{
    return m_adaptiveCard;
}

std::vector<std::shared_ptr<AdaptiveCardParseWarning>> ParseResult::GetWarnings() const
{
    return m_warnings;
}
