using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XceedTimeInput
    {
        public static FrameworkElement Render(AdaptiveTimeInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var timePicker = new TimePicker();
                DateTime value;
                if (DateTime.TryParse(input.Value, out value))
                    timePicker.Value = value;
                TimeSpan minValue;
                if (TimeSpan.TryParse(input.Min, out minValue))
                    timePicker.EndTime = minValue;
                TimeSpan maxValue;
                if (TimeSpan.TryParse(input.Max, out maxValue))
                    timePicker.EndTime = maxValue;
                timePicker.Watermark = input.Placeholder;
                timePicker.Style = context.GetStyle("Adaptive.Input.Time");
                timePicker.DataContext = input;
                context.InputBindings.Add(input.Id, () => ToIso8601Time(timePicker.Text));
                return timePicker;
            }
            else
            {
                var textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                return context.Render(textBlock);
            }

        }

        static string ToIso8601Time(string text)
        {
            if(string.IsNullOrEmpty(text))
                return string.Empty;

            DateTime dateTime;
            if(DateTime.TryParse(text, null, System.Globalization.DateTimeStyles.RoundtripKind, out dateTime))
                return dateTime.ToString("HH:mm");

            return text;
        }
    }
}