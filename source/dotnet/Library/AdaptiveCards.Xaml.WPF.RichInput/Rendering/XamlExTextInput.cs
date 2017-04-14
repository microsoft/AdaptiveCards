using System.Windows;
using System.Windows.Controls;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering
{
    public static class XamlExTextInput
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            TextInput input = (TextInput)element;
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var textBox = new WatermarkTextBox() { Text = input.Value };
                if (input.IsMultiline == true)
                {
                    textBox.AcceptsReturn = true;
                    textBox.TextWrapping = TextWrapping.Wrap;
                    textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
                }
                if (input.MaxLength > 0)
                    textBox.MaxLength = input.MaxLength;

                textBox.Watermark = input.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.{input.Style}");
                textBox.DataContext = input;
                context.InputBindings.Add(input.Id, () => textBox.Text);
                return textBox;
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