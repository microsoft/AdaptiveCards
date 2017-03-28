using System;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Renderers
{
    public partial class XamlRendererExtended : XamlRenderer
    {
        /// <summary>
        /// Input.Date
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(InputDate input, RenderContext context)
        {
            if (this.Options.SupportInteraction)
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
                datePicker.Style = this.GetStyle("Adaptive.Input.Date");
                datePicker.DataContext = input;
                context.InputControls.Add(datePicker);
                return datePicker;
            }
            else
            {
                var textBlock = new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder };
                return Render(textBlock, context);
            }
        }
    }
}