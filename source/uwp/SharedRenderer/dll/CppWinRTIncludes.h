// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifdef USE_WINUI3
#define Xaml_OM Winui3
#define Xaml_Rendering Winui3
#else
#define Xaml_OM Uwp
#define Xaml_Rendering Uwp
#endif

#include <winrt/base.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include <winrt/Windows.Media.Core.h>
#include <winrt/Windows.Media.Playback.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Filters.h>

#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Documents.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>

#include <winrt/AdaptiveCards.ObjectModel.Uwp.h>

namespace winrt
{
    using namespace ::winrt::Windows::Foundation;
    using namespace ::winrt::Windows::Foundation::Collections;
    using namespace ::winrt::Windows::Foundation::Numerics;
    using namespace ::winrt::Windows::Media::Core;
    using namespace ::winrt::Windows::Media::Playback;
    using namespace ::winrt::Windows::Storage::Streams;
    using namespace ::winrt::Windows::System;
    using namespace ::winrt::Windows::UI;

    namespace xaml = ::winrt::Windows::UI::Xaml;
    using namespace xaml;
    namespace xaml_controls = ::winrt::Windows::UI::Xaml::Controls;
    namespace xaml_automation = ::winrt::Windows::UI::Xaml::Automation;
    namespace xaml_documents = ::winrt::Windows::UI::Xaml::Documents;
    namespace xaml_input = ::winrt::Windows::UI::Xaml::Input;
    namespace xaml_markup = ::winrt::Windows::UI::Xaml::Markup;
    namespace xaml_media = ::winrt::Windows::UI::Xaml::Media;
    namespace xaml_media_imaging = ::winrt::Windows::UI::Xaml::Media::Imaging;
    namespace xaml_shapes = ::winrt::Windows::UI::Xaml::Shapes;

    using namespace ::winrt::AdaptiveCards::ObjectModel::Xaml_OM;

    // In order to avoid "namespace not defined" errors we have to define the namespace here too.
    namespace AdaptiveCards::Rendering::Xaml_Rendering{}
    namespace render_xaml = ::winrt::AdaptiveCards::Rendering::Xaml_Rendering;

    namespace AdaptiveCards::Rendering::Xaml_Rendering::implementation{}
    namespace implementation
    {
        using namespace ::winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation;
    }

    using JsonObject = ::winrt::Windows::Data::Json::JsonObject;

    using CoreWindow = ::winrt::Windows::UI::Core::CoreWindow;
    using CoreVirtualKeyStates = ::winrt::Windows::UI::Core::CoreVirtualKeyStates;
} // namespace winrt
