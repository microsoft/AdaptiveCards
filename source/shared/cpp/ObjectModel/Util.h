// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "BaseCardElement.h"
#include "AdaptiveCardParseWarning.h"

std::string ValidateColor(const std::string& backgroundColor, std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& warnings);

std::optional<int> ParseSizeForPixelSize(
    const std::string& sizeString, std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>* warnings);

void EnsureShowCardVersions(const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& actions, const std::string& version);

void HandleUnknownProperties(const Json::Value& json, const std::unordered_set<std::string>& knownProperties, Json::Value& unknownProperties);
