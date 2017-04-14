using System;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering
{
    public class XamlExDateInput : DateInput, IRender<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// Input.Date
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var datePicker = new DatePicker();
                datePicker.ToolTip = this.Placeholder;
                DateTime value;
                if (DateTime.TryParse(this.Value, out value))
                    datePicker.SelectedDate = value;
                DateTime minValue;
                if (DateTime.TryParse(this.Min, out minValue))
                    datePicker.DisplayDateStart = minValue;
                DateTime maxValue;
                if (DateTime.TryParse(this.Max, out maxValue))
                    datePicker.DisplayDateEnd = maxValue;
                datePicker.Style = context.GetStyle("Adaptive.Input.Date");
                datePicker.DataContext = this;
                context.InputBindings.Add(this.Id, () => datePicker.Text);
                return datePicker;
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