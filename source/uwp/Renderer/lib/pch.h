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
#define AdaptiveNamespaceStart namespace AdaptiveCards { namespace Rendering { namespace Uwp { 
#define AdaptiveNamespace AdaptiveCards::Rendering::Uwp
#define AdaptiveNamespaceEnd }}}
#define AdaptiveRuntimeClass RuntimeClass_AdaptiveCards_Rendering_Uwp
#define AdaptivePointerCast dynamic_pointer_cast
#endif

#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>
#include <unordered_map>
#include <set>
#include <ppltasks.h>
#include <sstream>

// The #define of this in winbase.h windows.ui.xaml.media.animation.h's IStoryboard defintion
// so we need to remove it
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include "ErrorHandling.h"
#include "Util.h"

#include "AdaptiveCards.Rendering.Uwp.h"
