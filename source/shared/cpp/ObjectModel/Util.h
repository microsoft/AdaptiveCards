#pragma once

#include "BaseCardElement.h"
#include "AdaptiveCardParseWarning.h"

std::string ValidateColor(const std::string& backgroundColor,
                          std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>& warnings);

int ParseSizeForPixelSize(const std::string& sizeString,
                          std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>* warnings);

void EnsureShowCardVersions(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& actions,
                            const std::string& version);
