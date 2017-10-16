using System;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{

    public static class XceedDateInput
    {
        public static FrameworkElement Render(AdaptiveDateInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var datePicker = new DatePicker();
                datePicker.ToolTip = input.Placeholder;
                DateTime value;
                if (DateTime.TryParse(input.Value, out value))
                    datePicker.SelectedDate = value;
                DateTime minValue;
                if (DateTime.TryParse(input.Min, out minValue))
                    datePicker.DisplayDateStart = minValue;
                DateTime maxValue;
                if (DateTime.TryParse(input.Max, out maxValue))
                    datePicker.DisplayDateEnd = maxValue;
                datePicker.Style = context.GetStyle("Adaptive.Input.Date");
                datePicker.DataContext = input;
                context.InputBindings.Add(input.Id, () => ToIso8601Date(datePicker.Text));
                return datePicker;
            }
            else
            {
                var textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                return context.Render(textBlock);
            }
        }

        static string ToIso8601Date(string text)
        {
            if (string.IsNullOrEmpty(text))
                return string.Empty;

            DateTime dateTime;
            if(DateTime.TryParse(text, null, System.Globalization.DateTimeStyles.RoundtripKind, out dateTime))
                return dateTime.ToString("yyyy-MM-dd");

            return text;
        }
    }
}