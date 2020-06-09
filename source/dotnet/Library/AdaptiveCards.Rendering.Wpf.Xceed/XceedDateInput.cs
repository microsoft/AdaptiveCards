// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
using System.Windows.Controls;
using System.Text.RegularExpressions;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XceedDateInput
    {
        static Regex textFunctionRegex;
        static XceedDateInput()
        {
            textFunctionRegex = new Regex(@"^(\d{4})-(\d{2})-(\d{2})$", RegexOptions.Compiled);
        }

        // Validate times are of the format YYYY-MM-DD. This allows us to check the string against a regular expression for
        // this format before passing to DateTime.TryParse to ensure we support only this single format.
        private static bool IsSupportedDateFormat(string dateString)
        {
            return (dateString != null) && textFunctionRegex.IsMatch(dateString);
        }

        public static FrameworkElement Render(AdaptiveDateInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var datePicker = new DatePicker();
                datePicker.ToolTip = input.Placeholder;
                DateTime value;
                if (IsSupportedDateFormat(input.Value) && DateTime.TryParse(input.Value, out value))
                    datePicker.SelectedDate = value;
                DateTime minValue;
                if (IsSupportedDateFormat(input.Min) && DateTime.TryParse(input.Min, out minValue))
                    datePicker.DisplayDateStart = minValue;
                DateTime maxValue;
                if (IsSupportedDateFormat(input.Max) && DateTime.TryParse(input.Max, out maxValue))
                    datePicker.DisplayDateEnd = maxValue;
                datePicker.Style = context.GetStyle("Adaptive.Input.Date");
                datePicker.DataContext = input;

                AdaptiveXceedDateInputValue inputValue = new AdaptiveXceedDateInputValue(input, datePicker);
                context.InputValues.Add(input.Id, inputValue);
                context.InputBindings.Add(input.Id, () => inputValue.GetValue());

                return datePicker;
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
