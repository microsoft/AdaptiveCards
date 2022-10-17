// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <winrt/base.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Filters.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.Documents.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Media.Core.h>
#include <winrt/Windows.Media.Playback.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/AdaptiveCards.ObjectModel.Uwp.h>
#include <winrt/Windows.UI.Text.h>

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
	using namespace ::winrt::Windows::UI::Xaml;
    using namespace ::winrt::Windows::UI::Xaml::Controls;
    using namespace ::winrt::Windows::UI::Xaml::Controls::Primitives;
    using namespace ::winrt::Windows::UI::Xaml::Automation;
	using namespace ::winrt::Windows::UI::Xaml::Automation::Peers;
    using namespace ::winrt::Windows::UI::Xaml::Documents;
    using namespace ::winrt::Windows::UI::Xaml::Input;
    using namespace ::winrt::Windows::UI::Xaml::Markup;
    using namespace ::winrt::Windows::UI::Xaml::Media::Imaging;
    using namespace ::winrt::Windows::UI::Xaml::Shapes;
    using namespace ::winrt::AdaptiveCards::ObjectModel::Uwp;
    
    // In order to avoid "namespace not defined" errors we have to define the namespace here too.
	namespace AdaptiveCards::Rendering::Uwp{}
	using namespace ::winrt::AdaptiveCards::Rendering::Uwp;

    namespace AdaptiveCards::Rendering::Uwp::implementation{}
    namespace implementation
    {
        using namespace ::winrt::AdaptiveCards::Rendering::Uwp::implementation;
    }

    using Brush = winrt::Windows::UI::Xaml::Media::Brush;
    using FontFamily = winrt::Windows::UI::Xaml::Media::FontFamily;
    using ImageBrush = ::winrt::Windows::UI::Xaml::Media::ImageBrush;
    using ImageSource = ::winrt::Windows::UI::Xaml::Media::ImageSource;
    using RectangleGeometry = winrt::Windows::UI::Xaml::Media::RectangleGeometry;
    using SolidColorBrush = ::winrt::Windows::UI::Xaml::Media::SolidColorBrush;
    using Stretch = ::winrt::Windows::UI::Xaml::Media::Stretch;
	using AlignmentX = ::winrt::Windows::UI::Xaml::Media::AlignmentX;
	using AlignmentY = ::winrt::Windows::UI::Xaml::Media::AlignmentY;

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
}
