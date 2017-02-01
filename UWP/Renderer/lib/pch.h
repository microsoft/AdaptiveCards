//
//    Copyright (C) Microsoft.  All rights reserved.
//
#pragma once

#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>

// The #define of this in winbase.h windows.ui.xaml.media.animation.h's IStoryboard defintion
// so we need to remove it
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include "ErrorHandling.h"

#include <ppltasks.h>