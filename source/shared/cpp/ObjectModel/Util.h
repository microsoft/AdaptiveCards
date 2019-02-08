#pragma once
#include <string>
#include <vector>
#include <memory>
#include "BaseCardElement.h"

void PropagateLanguage(const std::string& language,
                       const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& m_body);

std::string ValidateColor(const std::string& backgroundColor,
                          std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>& warnings);

void ValidateUserInputForDimensionWithUnit(const std::string& unit,
                                           const std::string& requestedDimension,
                                           int& parsedDimension,
                                           std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>& warnings);

bool ShouldParseForExplicitDimension(const std::string& input);

void EnsureShowCardVersions(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& actions,
                            const std::string& version);
