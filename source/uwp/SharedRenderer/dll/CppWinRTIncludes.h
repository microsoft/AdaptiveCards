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

// WinUI 2
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/Microsoft.UI.Xaml.Automation.Peers.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>

namespace winrt
{
    using namespace ::winrt::Windows::Foundation;
    using namespace ::winrt::Windows::Foundation::Collections;
    using namespace ::winrt::Windows::Foundation::Numerics;
    using namespace ::winrt::Windows::Media::Core;
    using namespace ::winrt::Windows::Media::Playback;
    using namespace ::winrt::Windows::Storage::Streams;
    using namespace ::winrt::Windows::System;

    // WinUI 2
    using namespace ::winrt::Microsoft::UI;
    namespace xaml = ::winrt::Microsoft::UI::Xaml;
    using namespace xaml;
    using namespace xaml::Controls;
    using namespace xaml::Controls::Primitives;
    using namespace xaml::Automation;
    using namespace xaml::Automation::Peers;

    using namespace ::winrt::Windows::UI::Xaml::Documents;
    using namespace ::winrt::Windows::UI::Xaml::Input;
    using namespace ::winrt::Windows::UI::Xaml::Markup;
    using namespace ::winrt::Windows::UI::Xaml::Media::Imaging;
    using namespace ::winrt::Windows::UI::Xaml::Shapes;

    using namespace ::winrt::AdaptiveCards::ObjectModel::Xaml_OM;

    // In order to avoid "namespace not defined" errors we have to define the namespace here too.
    namespace AdaptiveCards::Rendering::Xaml_Rendering{}
    using namespace ::winrt::AdaptiveCards::Rendering::Xaml_Rendering;

    namespace AdaptiveCards::Rendering::Xaml_Rendering::implementation{}
    namespace implementation
    {
        using namespace ::winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation;
    }

    using XamlReader = ::winrt::Windows::UI::Xaml::Markup::XamlReader;

    using AlignmentX = ::winrt::Windows::UI::Xaml::Media::AlignmentX;
    using AlignmentY = ::winrt::Windows::UI::Xaml::Media::AlignmentY;
    using Brush = winrt::Windows::UI::Xaml::Media::Brush;
    using FontFamily = winrt::Windows::UI::Xaml::Media::FontFamily;
    using ImageBrush = ::winrt::Windows::UI::Xaml::Media::ImageBrush;
    using ImageSource = ::winrt::Windows::UI::Xaml::Media::ImageSource;
    using RectangleGeometry = winrt::Windows::UI::Xaml::Media::RectangleGeometry;
    using SolidColorBrush = ::winrt::Windows::UI::Xaml::Media::SolidColorBrush;
    using Stretch = ::winrt::Windows::UI::Xaml::Media::Stretch;

    using UIElement = ::winrt::Windows::UI::Xaml::UIElement;
    using ResourceDictionary = ::winrt::Windows::UI::Xaml::ResourceDictionary;
    using RoutedEventArgs = ::winrt::Windows::UI::Xaml::RoutedEventArgs;
    using Selector = ::winrt::Windows::UI::Xaml::Controls::Primitives::Selector;
    using TextBox = ::winrt::Windows::UI::Xaml::Controls::TextBox;
    using TimePicker = ::winrt::Windows::UI::Xaml::Controls::TimePicker;
    using AutoSuggestBox = ::winrt::Windows::UI::Xaml::Controls::AutoSuggestBox;
    using Border = ::winrt::Windows::UI::Xaml::Controls::Border;
    using CalendarDatePicker = ::winrt::Windows::UI::Xaml::Controls::CalendarDatePicker;
    using CheckBox = ::winrt::Windows::UI::Xaml::Controls::CheckBox;
    using ColumnDefinition = ::winrt::Windows::UI::Xaml::Controls::ColumnDefinition;
    using ExceptionRoutedEventArgs = ::winrt::Windows::UI::Xaml::ExceptionRoutedEventArgs;
    using IFrameworkElement = ::winrt::Windows::UI::Xaml::IFrameworkElement;
    using FrameworkElement = ::winrt::Windows::UI::Xaml::FrameworkElement;
    using Image = ::winrt::Windows::UI::Xaml::Controls::Image;
    using Panel = ::winrt::Windows::UI::Xaml::Controls::Panel;
    using IPasswordBox = ::winrt::Windows::UI::Xaml::Controls::IPasswordBox;
    using PasswordBox = ::winrt::Windows::UI::Xaml::Controls::PasswordBox;
    using Thickness = ::winrt::Windows::UI::Xaml::Thickness;
    using DependencyObject = ::winrt::Windows::UI::Xaml::DependencyObject;
    using Button = ::winrt::Windows::UI::Xaml::Controls::Button;
    using AutomationPeer = ::winrt::Windows::UI::Xaml::Automation::Peers::AutomationPeer;
    using TextBlock= ::winrt::Windows::UI::Xaml::Controls::TextBlock;
    using ToolTip = ::winrt::Windows::UI::Xaml::Controls::ToolTip;
    using ToolTipService = ::winrt::Windows::UI::Xaml::Controls::ToolTipService;
    using AutomationProperties= ::winrt::Windows::UI::Xaml::Automation::AutomationProperties;
    using StackPanel = ::winrt::Windows::UI::Xaml::Controls::StackPanel;
    using TextAlignment = ::winrt::Windows::UI::Xaml::TextAlignment;
    using HorizontalAlignment = ::winrt::Windows::UI::Xaml::HorizontalAlignment;
    using VerticalAlignment = ::winrt::Windows::UI::Xaml::VerticalAlignment;
    using Orientation = ::winrt::Windows::UI::Xaml::Controls::Orientation;
    using Style = ::winrt::Windows::UI::Xaml::Style;
    using Grid = ::winrt::Windows::UI::Xaml::Controls::Grid;
    using MediaElement = ::winrt::Windows::UI::Xaml::Controls::MediaElement;
    using RichTextBlock = ::winrt::Windows::UI::Xaml::Controls::RichTextBlock;
    using Canvas = ::winrt::Windows::UI::Xaml::Controls::Canvas;
    using Visibility = ::winrt::Windows::UI::Xaml::Visibility;
    using AutomationControlType = ::winrt::Windows::UI::Xaml::Automation::Peers::AutomationControlType;
    using GridUnitType = ::winrt::Windows::UI::Xaml::GridUnitType;
    using MenuFlyout = ::winrt::Windows::UI::Xaml::Controls::MenuFlyout;
    using MenuFlyoutItem = ::winrt::Windows::UI::Xaml::Controls::MenuFlyoutItem;
    using RowDefinition = ::winrt::Windows::UI::Xaml::Controls::RowDefinition;
    using GridLength = ::winrt::Windows::UI::Xaml::GridLength;
    using TextWrapping = ::winrt::Windows::UI::Xaml::TextWrapping;
    using ContentControl = ::winrt::Windows::UI::Xaml::Controls::ContentControl;
    using SymbolIcon = ::winrt::Windows::UI::Xaml::Controls::SymbolIcon;
    using Symbol = ::winrt::Windows::UI::Xaml::Controls::Symbol;
    using RelativePanel = ::winrt::Windows::UI::Xaml::Controls::RelativePanel;
    using ComboBox = ::winrt::Windows::UI::Xaml::Controls::ComboBox;
    using ComboBoxItem = ::winrt::Windows::UI::Xaml::Controls::ComboBoxItem;
    using FlowDirection = ::winrt::Windows::UI::Xaml::FlowDirection;
    using RadioButton = ::winrt::Windows::UI::Xaml::Controls::RadioButton;
    using ButtonBase = ::winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase;
    using Control = ::winrt::Windows::UI::Xaml::Controls::Control;
    using FocusState = ::winrt::Windows::UI::Xaml::FocusState;
    using TextTrimming = ::winrt::Windows::UI::Xaml::TextTrimming;
    using AutomationHeadingLevel = ::winrt::Windows::UI::Xaml::Automation::Peers::AutomationHeadingLevel;
    using AutoSuggestBoxTextChangedEventArgs = ::winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs;
    using VariableSizedWrapGrid = ::winrt::Windows::UI::Xaml::Controls::VariableSizedWrapGrid;
    using OpticalMarginAlignment = ::winrt::Windows::UI::Xaml::OpticalMarginAlignment;
    using IButtonWithFlyout = ::winrt::Windows::UI::Xaml::Controls::IButtonWithFlyout;
    using ToggleButton = ::winrt::Windows::UI::Xaml::Controls::Primitives::ToggleButton;
    using IFrameworkElementStatics = ::winrt::Windows::UI::Xaml::IFrameworkElementStatics;

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
