//
//    Copyright (C) Microsoft.  All rights reserved.
//
#pragma once

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
