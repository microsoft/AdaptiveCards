#pragma once

#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <locale>
#include <memory>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <typeindex>

#if defined(USE_CPPCORECHECK)
#undef USE_CPPCORECHECK
#endif

#include "Enums.h"
#include "Formatter.h"
#include "RenderEnums.h"
#include "Utils.h"

#include "BaseElement.h"
#include "HostConfig.h"
#include "SharedAdaptiveCard.h"

#include "QmlTag.h"
#include "AdaptiveCardDependency.h"

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
