#pragma once

#ifdef ADAPTIVE_CARDS_WINDOWS
#include "winPch.h"
#endif

#ifndef AdaptiveSharedNamespace
#define AdaptiveSharedNamespace AdaptiveCards
#endif

#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <functional>
#include <locale>
#include <memory>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#if defined(_MSC_BUILD) && !defined(__ANDROID__) && !defined(__APPLE__) && !defined(ADAPTIVE_CARDS_WINDOWS)
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
