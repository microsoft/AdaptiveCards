using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering
{
    public static class XamlExNumberInput
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            NumberInput input = (NumberInput)element;
            if (context.Config.SupportsInteractivity)
            {

                IntegerUpDown numberPicker = new IntegerUpDown();
                // numberPicker.ShowButtonSpinner = true;

                if (!Double.IsNaN(input.Value))
                    numberPicker.Value = Convert.ToInt32(input.Value);

                if (!Double.IsNaN(input.Min))
                    numberPicker.Minimum = Convert.ToInt32(input.Min);

                if (!Double.IsNaN(input.Max))
                    numberPicker.Minimum = Convert.ToInt32(input.Max);

                numberPicker.Watermark = input.Placeholder;
                numberPicker.Style = context.GetStyle("Adaptive.Input.Number");
                numberPicker.DataContext = input;
                context.InputBindings.Add(input.Id, () => numberPicker.Value);
                return numberPicker;
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