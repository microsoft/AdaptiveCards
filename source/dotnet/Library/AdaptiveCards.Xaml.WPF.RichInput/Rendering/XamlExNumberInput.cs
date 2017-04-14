using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering
{
    public class XamlExNumberInput : NumberInput, IRender<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// this.Number
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {

                IntegerUpDown numberPicker = new IntegerUpDown();
                // numberPicker.ShowButtonSpinner = true;

                if (!Double.IsNaN(this.Value))
                    numberPicker.Value = Convert.ToInt32(this.Value);

                if (!Double.IsNaN(this.Min))
                    numberPicker.Minimum = Convert.ToInt32(this.Min);

                if (!Double.IsNaN(this.Max))
                    numberPicker.Minimum = Convert.ToInt32(this.Max);

                numberPicker.Watermark = this.Placeholder;
                numberPicker.Style = context.GetStyle("Adaptive.Input.Number");
                numberPicker.DataContext = this;
                context.InputBindings.Add(this.Id, () => numberPicker.Value);
                return numberPicker;
            }
            else
            {
                var textBlock = TypedElementConverter.CreateElement<TextBlock>("TextBlock");
                textBlock.Text = XamlUtilities.GetFallbackText(this) ?? this.Placeholder;
                return context.Render(textBlock);
            }

        }
    }
}