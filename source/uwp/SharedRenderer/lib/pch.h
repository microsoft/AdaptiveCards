// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

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

#define FACILITY_ADAPTIVECARDS 0xADA
#define ERRORBASE_ADAPTIVECARDS 0x1000
#define E_PERFORM_FALLBACK MAKE_HRESULT(1, FACILITY_ADAPTIVECARDS, ERRORBASE_ADAPTIVECARDS)
#define E_FALLBACK_NOT_FOUND MAKE_HRESULT(2, FACILITY_ADAPTIVECARDS, ERRORBASE_ADAPTIVECARDS)

#include "dll\CppWinRTIncludes.h"

// The #define of this in winbase.h windows.ui.xaml.media.animation.h's IStoryboard defintion
// so we need to remove it
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

// Shared Model headers
#include "Enums.h"
#include "HostConfig.h"

// Commonly-used AdaptiveCardRenderer headers
#include "AdaptiveRenderContext.h"
#include "Util.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"

namespace XamlHelpers = ::AdaptiveCards::Rendering::Xaml_Rendering::XamlHelpers;

#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev, fac, code) \
    ((HRESULT)(((unsigned long)(sev) << 31) | ((unsigned long)(fac) << 16) | ((unsigned long)(code))))
#endif
