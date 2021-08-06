// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#define AdaptiveRuntime(cls) InspectableClass(RuntimeClass_AdaptiveCards_ObjectModel_Uwp_##cls, BaseTrust)
#define AdaptiveRuntimeStatic(cls) InspectableClassStatic(RuntimeClass_AdaptiveCards_ObjectModel_Uwp_##cls, BaseTrust)
#define AdaptiveRuntimeStringClass(cls) InspectableClass(L"AdaptiveCards.ObjectModel.Uwp." L#cls, BaseTrust)
#define AdaptiveRuntimeClass RuntimeClass_AdaptiveCards_ObjectModel_Uwp
#define AdaptivePointerCast dynamic_pointer_cast

// don't want windows.h min()/max() definitions as they conflict with std::numeric_limits<T>::min()/max()
#ifndef NOMINMAX
#define NOMINMAX
#endif

#define DISABLE_NS_PREFIX_CHECKS 1
#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>
#include <unordered_map>
#include <set>
#include <ppltasks.h>
#include <sstream>
#include <limits>
#include <string>

// Shared Model headers
#include "Enums.h"
#include "HostConfig.h"

// Commonly-used AdaptiveCardRenderer headers
#include "AdaptiveCards.ObjectModel.Uwp.h"
#include "AdaptiveCardElement.h"
#include "ErrorHandling.h"
#include "ObjectModelUtil.h"
#include "Vector.h"

#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev, fac, code) \
    ((HRESULT)(((unsigned long)(sev) << 31) | ((unsigned long)(fac) << 16) | ((unsigned long)(code))))
#endif

#define FACILITY_ADAPTIVECARDS 0xADA
#define ERRORBASE_ADAPTIVECARDS 0x1000
#define E_PERFORM_FALLBACK MAKE_HRESULT(1, FACILITY_ADAPTIVECARDS, ERRORBASE_ADAPTIVECARDS)

#include <windows.foundation.h>
#include <windows.foundation.collections.h>

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/AdaptiveCards.ObjectModel.Uwp.h>
