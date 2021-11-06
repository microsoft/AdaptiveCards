// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#define AdaptiveRuntime(cls) InspectableClass(RuntimeClass_AdaptiveCards_Rendering_WinUI3_##cls, BaseTrust)
#define AdaptiveRuntimeStatic(cls) InspectableClassStatic(RuntimeClass_AdaptiveCards_Rendering_WinUI3_##cls, BaseTrust)
#define AdaptiveRuntimeStringClass(cls) InspectableClass(L"AdaptiveCards.Rendering.WinUI3." L#cls, BaseTrust)
#define AdaptiveRuntimeClass RuntimeClass_AdaptiveCards_Rendering_WinUI3
#define AdaptivePointerCast dynamic_pointer_cast

// don't want windows.h min()/max() definitions as they conflict with std::numeric_limits<T>::min()/max()
#ifndef NOMINMAX
#define NOMINMAX
#endif

#define DISABLE_NS_PREFIX_CHECKS 1
#include <wil/cppwinrt.h>
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

#include <windows.foundation.h>
#include <windows.foundation.collections.h>
#include <windows.ui.xaml.shapes.h>
#include <windows.ui.xaml.markup.h>

#include <winrt/base.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/AdaptiveCards.Rendering.WinUI3.h>
#include <winrt/AdaptiveCards.ObjectModel.WinUI3.h>

// The #define of this in winbase.h windows.ui.xaml.media.animation.h's IStoryboard defintion
// so we need to remove it
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

// Shared Model headers
#include "Enums.h"
#include "HostConfig.h"

// Commonly-used AdaptiveCardRenderer headers
#include "AdaptiveCards.Rendering.WinUI3.h"
#include "Util.h"
#include "Vector.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"

#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev, fac, code) \
    ((HRESULT)(((unsigned long)(sev) << 31) | ((unsigned long)(fac) << 16) | ((unsigned long)(code))))
#endif

