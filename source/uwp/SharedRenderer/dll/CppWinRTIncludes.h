// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifndef USE_WINUI3
#define Xaml_OM Uwp
#else
#define Xaml_OM Winui3
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
    using namespace xaml::Controls;
    using namespace xaml::Controls::Primitives;
    using namespace xaml::Automation;
    using namespace xaml::Automation::Peers;
    using namespace xaml::Documents;
    using namespace xaml::Input;
    using namespace xaml::Media::Imaging;
    using namespace xaml::Shapes;

    using namespace ::winrt::AdaptiveCards::ObjectModel::Xaml_OM;

    // In order to avoid "namespace not defined" errors we have to define the namespace here too.
    namespace AdaptiveCards::Rendering::Uwp{}
    using namespace ::winrt::AdaptiveCards::Rendering::Uwp;

    // winrt_render_xaml namespace alias used to differentiate in cases where a type exists in both
    // the renderer and the object model (ie. ActionMode)
    namespace winrt_render_xaml = ::winrt::AdaptiveCards::Rendering::Uwp;

    namespace AdaptiveCards::Rendering::Uwp::implementation{}
    namespace implementation
    {
        using namespace ::winrt::AdaptiveCards::Rendering::Uwp::implementation;
    }

    using XamlReader = xaml::Markup::XamlReader;

    using AlignmentX = xaml::Media::AlignmentX;
    using AlignmentY = xaml::Media::AlignmentY;
    using Brush = xaml::Media::Brush;
    using FontFamily = xaml::Media::FontFamily;
    using ImageBrush = xaml::Media::ImageBrush;
    using ImageSource = xaml::Media::ImageSource;
    using RectangleGeometry = xaml::Media::RectangleGeometry;
    using SolidColorBrush = xaml::Media::SolidColorBrush;
    using Stretch = xaml::Media::Stretch;

    // using namespace winrt::Windows::Data::Json
    using JsonObject = ::winrt::Windows::Data::Json::JsonObject;

    // using namespace winrt::Windows::Data::Xml::Dom
    using XmlDocument = ::winrt::Windows::Data::Xml::Dom::XmlDocument;
    using IXmlNode = ::winrt::Windows::Data::Xml::Dom::IXmlNode;

    // using namespace winrt::Windows::Globalization::DateTimeFormatting;
    using DateTimeFormatter = ::winrt::Windows::Globalization::DateTimeFormatting::DateTimeFormatter;

    // using namespace winrt::Windows::UI::Core;
    using CoreWindow = ::winrt::Windows::UI::Core::CoreWindow;
    using CoreVirtualKeyStates = ::winrt::Windows::UI::Core::CoreVirtualKeyStates;

    // using namespace winrt::Windows::Web::Http
    using HttpProgress = ::winrt::Windows::Web::Http::HttpProgress;
    using HttpClient = ::winrt::Windows::Web::Http::HttpClient;

    // using namespace winrt::Windows::Web::Http::HttpFilters
    using HttpBaseProtocolFilter = ::winrt::Windows::Web::Http::Filters::HttpBaseProtocolFilter;

    // using namespace winrt::Windows::UI::Text
    using TextDecorations = ::winrt::Windows::UI::Text::TextDecorations;
} // namespace winrt
