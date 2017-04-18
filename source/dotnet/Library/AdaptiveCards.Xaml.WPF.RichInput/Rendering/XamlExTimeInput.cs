using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering
{
    public static class XamlExTimeInput
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            TimeInput input = (TimeInput)element;
            if (context.Options.SupportsInteractivity)
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
                context.InputBindings.Add(input.Id, () => timePicker.Text);
                return timePicker;
            }
            else
            {
                var textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                return context.Render(textBlock);
            }

        }
    }
}