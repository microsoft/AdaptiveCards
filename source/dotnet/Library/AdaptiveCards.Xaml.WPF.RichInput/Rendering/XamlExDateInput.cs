using System;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering
{

    public static class XamlExDateInput
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            DateInput input = (DateInput)element;
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
                var textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                return context.Render(textBlock);
            }
        }

        static string ToIso8601Date(string text)
        {
            if (string.IsNullOrEmpty(text))
                return string.Empty;

            DateTime dateTime;
            var parsed = DateTime.TryParse(text, null, System.Globalization.DateTimeStyles.RoundtripKind, out dateTime);
            if (!parsed)
                return string.Empty;

            return dateTime.ToString("yyyy-MM-dd");
        }
    }
}