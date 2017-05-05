using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlDateInput
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            DateInput input = (DateInput)element;

            if (context.Config.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = input.Value };
                textBox.Text = input.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.Date");
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
                if (input.Value != null)
                {
                    textBlock = TypedElementConverter.CreateElement<TextBlock>();
                    textBlock.Text = input.Value;
                    textBlock.Color = TextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }
        }
    }
}