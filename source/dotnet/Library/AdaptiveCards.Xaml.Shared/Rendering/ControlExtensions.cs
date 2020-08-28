// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
#if WPF
using System.Windows.Controls;
using System.Windows.Documents;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class ControlExtensions
    {
        public static object GetContext(this FrameworkElement element)
        {
#if WPF
            return element?.DataContext;
#elif XAMARIN
            return element?.BindingContext;
#endif
        }

        public static void SetContext(this FrameworkElement element, object value)
        {
#if WPF
            element.DataContext = value;
#elif XAMARIN
            element.BindingContext = value;
#endif
        }

        public static void SetState(this CheckBox control, bool value)
        {
            control.IsChecked = value;
        }

        public static bool? GetState(this CheckBox control)
        {
            return control.IsChecked;
        }

#if WPF
        public static void Add(this ListBox control, object element)
        {
            control.Items.Add(element);
        }
#endif

        public static void SetColor(this TextBlock textBlock, AdaptiveTextColor color, bool isSubtle, AdaptiveRenderContext context)
        {
            FontColorConfig colorOption = context.GetForegroundColors(color);
            string colorCode = isSubtle ? colorOption.Subtle : colorOption.Default;
#if WPF
            textBlock.Foreground = context.GetColorBrush(colorCode);
#elif XAMARIN
           textBlock.TextColor = context.GetColor(colorCode);
#endif
        }

        public static void SetColor(this Span inlineRun, AdaptiveTextColor color, bool isSubtle, AdaptiveRenderContext context)
        {
            FontColorConfig colorOption = context.GetForegroundColors(color);
            string colorCode = isSubtle ? colorOption.Subtle : colorOption.Default;
#if WPF
            inlineRun.Foreground = context.GetColorBrush(colorCode);
#elif XAMARIN
            inlineRun.ForegroundColor = context.GetColor(colorCode);
#endif
        }

        public static void SetHighlightColor(this Span inlineRun, AdaptiveTextColor color, bool isSubtle, AdaptiveRenderContext context)
        {
            FontColorConfig colorOption = context.GetForegroundColors(color);
            string colorCode = isSubtle ? colorOption.HighlightColors.Subtle : colorOption.HighlightColors.Default;
#if WPF
            inlineRun.Background = context.GetColorBrush(colorCode);
#elif XAMARIN
            inlineRun.BackgroundColor = context.GetColor(colorCode);
#endif
        }

#if WPF
        public static void SetHorizontalAlignment(this Image image, AdaptiveHorizontalAlignment alignment)
        {
            if (Enum.TryParse(alignment.ToString(), out HorizontalAlignment a))
                image.HorizontalAlignment = a;
        }

        public static void SetBackgroundColor(this Panel panel, string color, AdaptiveRenderContext context)
        {
            panel.Background = context.GetColorBrush(color);
        }
#endif

        public static void SetHeight(this FrameworkElement element, double height)
        {
#if WPF
            element.Height = height;
#elif XAMARIN
            element.HeightRequest = height;
#endif
        }

        public static void SetBackgroundColor(this Button panel, string color, AdaptiveRenderContext context)
        {
#if WPF
            panel.Background = context.GetColorBrush(color);
#elif XAMARIN
            panel.BackgroundColor = context.GetColor(color);
#endif
        }

        public static void SetBorderColor(this Button view, string color, AdaptiveRenderContext context)
        {
#if WPF
            view.BorderBrush = context.GetColorBrush(color);
#elif XAMARIN
            view.BorderColor = context.GetColor(color);
#endif
        }

        public static void SetBorderThickness(this Button view, double thickness)
        {
#if WPF
            view.BorderThickness = new Thickness(thickness);
#elif XAMARIN
            view.BorderWidth = thickness;
#endif
        }

#if WPF
        public static void SetFontWeight(this System.Windows.Controls.TextBlock textBlock, int weight)
        {
            textBlock.FontWeight = FontWeight.FromOpenTypeWeight(weight);
        }
#elif XAMARIN
        public static void SetFontWeight(this TextBlock textBlock, int weight)
        { }
#endif

            public static void SetPlaceholder(this TextBox textBlock, string placeholder)
        {
            //UWP doesnt have the concept of placeholder for TextBox
#if XAMARIN
            textBlock.Placeholder = placeholder;
#endif
        }
    }
}
