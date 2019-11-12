// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
//    Copyright (C) Microsoft.  All rights reserved.
//
#pragma once

#ifdef ADAPTIVE_CARDS_WINDOWS
#include "winPch.h"
#else
#define AdaptiveRuntime(cls) InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_##cls, BaseTrust)
#define AdaptiveRuntimeStatic(cls) InspectableClassStatic(RuntimeClass_AdaptiveCards_Rendering_Uwp_##cls, BaseTrust)
#define AdaptiveRuntimeStringClass(cls) InspectableClass(L"AdaptiveCards.Rendering.Uwp." L#cls, BaseTrust)
#define AdaptiveNamespace AdaptiveCards::Rendering::Uwp
#define AdaptiveRuntimeClass RuntimeClass_AdaptiveCards_Rendering_Uwp
#define AdaptivePointerCast dynamic_pointer_cast
#endif

#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>
#include <unordered_map>
#include <set>
#include <ppltasks.h>
#include <sstream>
#include <limits>
#include <string>

// The #define of this in winbase.h windows.ui.xaml.media.animation.h's IStoryboard defintion
// so we need to remove it
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

// Shared Model headers
#include "Enums.h"
#include "HostConfig.h"

// Commonly-used AdaptiveCardRenderer headers
#include "AdaptiveCards.Rendering.Uwp.h"
#include "AdaptiveCardElement.h"
#include "ErrorHandling.h"
#include "Util.h"
#include "Vector.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"

#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev, fac, code) \
    ((HRESULT)(((unsigned long)(sev) << 31) | ((unsigned long)(fac) << 16) | ((unsigned long)(code))))
#endif

#define FACILITY_ADAPTIVECARDS 0xADA
#define ERRORBASE_ADAPTIVECARDS 0x1000
#define E_PERFORM_FALLBACK MAKE_HRESULT(1, FACILITY_ADAPTIVECARDS, ERRORBASE_ADAPTIVECARDS)

#include <windows.foundation.h>
#include <windows.foundation.collections.h>
#include <windows.ui.xaml.shapes.h>
#include <windows.ui.xaml.markup.h>

#include <winrt/base.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
