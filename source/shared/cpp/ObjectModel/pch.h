// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <functional>
#include <locale>
#include <memory>
#include <numeric>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#if defined(_MSC_BUILD) && !defined(__ANDROID__) && !defined(__APPLE__)
#define USE_CPPCORECHECK
#endif

#ifdef USE_CPPCORECHECK
#include <CppCoreCheck\warnings.h>
#pragma warning(disable : ALL_CPPCORECHECK_WARNINGS)
#pragma warning(default : CPPCORECHECK_ARITHMETIC_WARNINGS)
#pragma warning(default : CPPCORECHECK_BOUNDS_WARNINGS)
#pragma warning(default : CPPCORECHECK_CLASS_WARNINGS)
#pragma warning(default : CPPCORECHECK_CONCURRENCY_WARNINGS)
#pragma warning(default : CPPCORECHECK_CONST_WARNINGS)
#pragma warning(default : CPPCORECHECK_DECLARATION_WARNINGS)
#pragma warning(default : CPPCORECHECK_OWNER_POINTER_WARNINGS)
#pragma warning(default : CPPCORECHECK_RAW_POINTER_WARNINGS)
#pragma warning(default : CPPCORECHECK_SHARED_POINTER_WARNINGS)
#pragma warning(default : CPPCORECHECK_STYLE_WARNINGS)
#pragma warning(default : CPPCORECHECK_TYPE_WARNINGS)
#pragma warning(default : CPPCORECHECK_UNIQUE_POINTER_WARNINGS)
#endif

#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
    constexpr const char* const c_sharedModelVersion = "1.5";
}
