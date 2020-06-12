// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
using Xceed.Wpf.Toolkit;
using System.Text.RegularExpressions;

namespace AdaptiveCards.Rendering.Wpf
{

    public static class XceedTimeInput
    {
        static Regex TextFunctionRegex;
        static XceedTimeInput()
        {
            TextFunctionRegex = new Regex(@"^(\d{2}):(\d{2})$", RegexOptions.Compiled);
        }

        // Validate times are of the format HH:MM. This allows us to check the string against a regular expression for
        // this format before passing to DateTime.TryParse or TimeSpan.TryParse to ensure we support only this single format.
        private static bool IsSupportedTimeFormat(string timeString)
        {
            return (timeString != null) && TextFunctionRegex.IsMatch(timeString);
        }

        public static FrameworkElement Render(AdaptiveTimeInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var timePicker = new TimePicker();
                DateTime value;
                if (IsSupportedTimeFormat(input.Value) && DateTime.TryParse(input.Value, out value))
                    timePicker.Value = value;
                TimeSpan minValue;
                if (IsSupportedTimeFormat(input.Min) && TimeSpan.TryParse(input.Min, out minValue))
                    timePicker.StartTime = minValue;
                TimeSpan maxValue;
                if (IsSupportedTimeFormat(input.Max) && TimeSpan.TryParse(input.Max, out maxValue))
                    timePicker.EndTime = maxValue;
                timePicker.Watermark = input.Placeholder;
                timePicker.Style = context.GetStyle("Adaptive.Input.Time");
                timePicker.DataContext = input;

                context.InputValues.Add(input.Id, new AdaptiveXceedTimeInputValue(input, timePicker));

                return timePicker;
            }
            else
            {
                var textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                return context.Render(textBlock);
            }
        }
       
    }
}
