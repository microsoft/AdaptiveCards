using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering
{
    public class XamlExTimeInput : TimeInput, IRender<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// this.Time
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var timePicker = new TimePicker();
                DateTime value;
                if (DateTime.TryParse(this.Value, out value))
                    timePicker.Value = value;
                TimeSpan minValue;
                if (TimeSpan.TryParse(this.Min, out minValue))
                    timePicker.EndTime = minValue;
                TimeSpan maxValue;
                if (TimeSpan.TryParse(this.Max, out maxValue))
                    timePicker.EndTime = maxValue;
                timePicker.Watermark = this.Placeholder;
                timePicker.Style = context.GetStyle("Adaptive.Input.Time");
                timePicker.DataContext = this;
                context.InputBindings.Add(this.Id, () => timePicker.Text);
                return timePicker;
            }
            else
            {
                var textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(this) ?? this.Placeholder;
                return context.Render(textBlock);
            }

        }
    }
}