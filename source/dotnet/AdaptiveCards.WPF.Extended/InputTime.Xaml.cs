using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Renderers
{
    public partial class XamlRendererExtended : XamlRenderer
    {

        /// <summary>
        /// Input.Time
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(InputTime input, RenderContext context)
        {

            if (this.Options.SupportInteraction)
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
                timePicker.Style = this.GetStyle("Adaptive.Input.Time");
                timePicker.DataContext = input;
                context.InputControls.Add(timePicker);
                return timePicker;
            }
            else
            {
                var textBlock = new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder };
                return Render(textBlock, context);
            }

        }
    }
}