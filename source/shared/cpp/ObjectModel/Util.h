#pragma once
#include <string>
#include <vector>
#include <memory>
#include "BaseCardElement.h"

using namespace AdaptiveSharedNamespace;

void PropagateLanguage(const std::string& language, std::vector<std::shared_ptr<BaseCardElement>>& m_body);