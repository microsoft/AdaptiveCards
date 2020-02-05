// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class ControlExtensions
    {
        public static object GetContext(this FrameworkElement element)
        {
            return element?.DataContext;
        }

        public static void SetContext(this FrameworkElement element, object value)
        {
            element.DataContext = value;
        }

        public static void SetState(this CheckBox control, bool value)
        {
            control.IsChecked = value;
        }

        public static bool? GetState(this CheckBox control)
        {
            return control.IsChecked;
        }

        public static void Add(this ListBox control, object element)
        {
            control.Items.Add(element);
        }

        public static void SetColor(this TextBlock textBlock, AdaptiveTextColor color, bool isSubtle, AdaptiveRenderContext context)
        {
            FontColorConfig colorOption = context.GetForegroundColors(color);
            string colorCode = isSubtle ? colorOption.Subtle : colorOption.Default;
            textBlock.Foreground = context.GetColorBrush(colorCode);
        }

        public static void SetColor(this Span inlineRun, AdaptiveTextColor color, bool isSubtle, AdaptiveRenderContext context)
        {
            FontColorConfig colorOption = context.GetForegroundColors(color);
            string colorCode = isSubtle ? colorOption.Subtle : colorOption.Default;
            inlineRun.Foreground = context.GetColorBrush(colorCode);
        }

        public static void SetHighlightColor(this Span inlineRun, AdaptiveTextColor color, bool isSubtle, AdaptiveRenderContext context)
        {
            FontColorConfig colorOption = context.GetForegroundColors(color);
            string colorCode = isSubtle ? colorOption.HighlightColors.Subtle : colorOption.HighlightColors.Default;
            inlineRun.Background = context.GetColorBrush(colorCode);
        }

        public static void SetHorizontalAlignment(this Image image, AdaptiveHorizontalAlignment alignment)
        {
            if (Enum.TryParse(alignment.ToString(), out HorizontalAlignment a))
                image.HorizontalAlignment = a;
        }

        public static void SetBackgroundColor(this Panel panel, string color, AdaptiveRenderContext context)
        {
            panel.Background = context.GetColorBrush(color);
        }

        public static void SetHeight(this FrameworkElement element, double height)
        {
            element.Height = height;
        }

        public static void SetBackgroundColor(this Button panel, string color, AdaptiveRenderContext context)
        {
            panel.Background = context.GetColorBrush(color);
        }

        public static void SetBorderColor(this Button view, string color, AdaptiveRenderContext context)
        {
            view.BorderBrush = context.GetColorBrush(color);
        }

        public static void SetBorderThickness(this Button view, double thickness)
        {
            view.BorderThickness = new Thickness(thickness);
        }

        public static void SetFontWeight(this System.Windows.Controls.TextBlock textBlock, int weight)
        {
            textBlock.FontWeight = FontWeight.FromOpenTypeWeight(weight);
        }

        public static void SetPlaceholder(this TextBox textBlock, string placeholder)
        {
            //UWP doesnt have the concept of placeholder for TextBox
        }
    }
}
