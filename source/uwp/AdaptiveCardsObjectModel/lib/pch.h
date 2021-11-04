// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#define AdaptivePointerCast dynamic_pointer_cast

// don't want windows.h min()/max() definitions as they conflict with std::numeric_limits<T>::min()/max()
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <wil/cppwinrt.h>
#include <wil/result_macros.h>

#define DISABLE_NS_PREFIX_CHECKS 1
#include <unordered_map>
#include <set>
#include <sstream>
#include <limits>
#include <string>

// Shared Model headers
#include "Enums.h"
#include "HostConfig.h"

#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev, fac, code) \
    ((HRESULT)(((unsigned long)(sev) << 31) | ((unsigned long)(fac) << 16) | ((unsigned long)(code))))
#endif

#define FACILITY_ADAPTIVECARDS 0xADA
#define ERRORBASE_ADAPTIVECARDS 0x1000
#define E_PERFORM_FALLBACK MAKE_HRESULT(1, FACILITY_ADAPTIVECARDS, ERRORBASE_ADAPTIVECARDS)

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/AdaptiveCards.ObjectModel.Uwp.h>
#include <winrt/Windows.Data.Json.h>

// Commonly-used AdaptiveCardRenderer headers
#include "ObjectModelUtil.h"
#include "AdaptiveCardElement.h"
