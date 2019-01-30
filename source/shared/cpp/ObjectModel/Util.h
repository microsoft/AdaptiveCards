#pragma once
#include <string>
#include <vector>
#include <memory>
#include "BaseCardElement.h"

void PropagateLanguage(const std::string& language,
                       const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& m_body);

std::string ValidateColor(const std::string& backgroundColor,
                          std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>& warnings);

int ParseSizeForPixelSize(std::string& sizeString,
                          std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>* warnings);

void EnsureShowCardVersions(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& actions,
                            const std::string& version);
