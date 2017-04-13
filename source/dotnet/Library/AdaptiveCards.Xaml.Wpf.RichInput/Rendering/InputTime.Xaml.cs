using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering
{
    public partial class XamlRendererExtended : XamlRenderer
    {

        /// <summary>
        /// Input.Time
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected static FrameworkElement RenderInputTimeEx(TypedElement element, RenderContext context)
        {
            InputTime input = (InputTime)element;
            if (context.Options.AdaptiveCard.SupportsInteractivity)
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
                context.InputControls.Add(timePicker);
                return timePicker;
            }
            else
            {
                var textBlock = new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder };
                return context.Render(textBlock);
            }

        }
    }
}