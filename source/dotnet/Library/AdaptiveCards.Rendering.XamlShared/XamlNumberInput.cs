using System.Windows;
using System.Windows.Controls;

#if WPF

#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XamlNumberInput
    {
        public static FrameworkElement Render(NumberInput input, RenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = input.Value.ToString() };
				textBox.SetPlaceholder(input.Placeholder);
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.Number");
                textBox.SetContext(input);
                context.InputBindings.Add(input.Id, () => textBox.Text);
                return textBox;
            }
            else
            {
                Container container = TypedElementConverter.CreateElement<Container>();
                container.Separation = input.Separation;
                TextBlock textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                container.Items.Add(textBlock);
                if (input.Value != double.NaN)
                {
                    textBlock = TypedElementConverter.CreateElement<TextBlock>();
                    textBlock.Text = input.Value.ToString();
                    textBlock.Color = TextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }
        }
    }
}