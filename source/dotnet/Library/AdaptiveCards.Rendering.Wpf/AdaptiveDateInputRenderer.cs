using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveDateInputRenderer
    {
        public static FrameworkElement Render(AdaptiveDateInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = input.Value };
				textBox.SetPlaceholder(input.Placeholder);
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.Date");
                textBox.SetContext(input);
                context.InputBindings.Add(input.Id, () => textBox.Text);
                return textBox;
            }
            else
            {
                var container = AdaptiveTypedElementConverter.CreateElement<AdaptiveContainer>();
                container.Spacing = input.Spacing;
                container.Separator = input.Separator;
                var textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                container.Items.Add(textBlock);
                if (input.Value != null)
                {
                    textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                    textBlock.Text = input.Value;
                    textBlock.Color = AdaptiveTextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }
        }
    }
}