#pragma once

#include "AdaptiveCardParseWarning.h"

std::string ValidateColor(const std::string& backgroundColor,
                          std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>& warnings);

int ParseSizeForPixelSize(const std::string& sizeString,
                          std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>* warnings);

void EnsureShowCardVersions(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& actions,
                            const std::string& version);

void HandleUnknownProperties(const Json::Value& json, const std::unordered_set<std::string>& knownProperties, Json::Value& unknownProperties);
