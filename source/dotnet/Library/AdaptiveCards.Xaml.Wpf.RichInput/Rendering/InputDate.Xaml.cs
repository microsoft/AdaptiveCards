using System;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering
{
    public partial class XamlRendererExtended : XamlRenderer
    {
        /// <summary>
        /// Input.Date
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected static FrameworkElement RenderInputDateEx(TypedElement element, RenderContext context)
        {
            InputDate input = (InputDate)element;
            if (context.Options.AdaptiveCard.SupportsInteractivity)
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
                context.InputControls.Add(datePicker);
                return datePicker;
            }
            else
            {
                var textBlock = new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder };
                return context.Render(textBlock);
            }
        }
    }
}