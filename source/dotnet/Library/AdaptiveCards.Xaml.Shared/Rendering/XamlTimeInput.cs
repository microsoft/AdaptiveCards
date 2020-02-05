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
    public static class XamlTimeInput
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveTimeInput input = (AdaptiveTimeInput)element;
            if (context.Config.SupportsInteractivity)
            {
                var textBox = new TextBox() { Text = input.Value };
				textBox.SetPlaceholder(input.Placeholder);
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.Time");
                textBox.SetContext(input);
                context.InputBindings.Add(input.Id, () => textBox.Text);
                return textBox;
            }
            else
            {
                AdaptiveContainer container = AdaptiveTypedElementConverter.CreateElement<AdaptiveContainer>();
                container.Separator = input.Separator;
                container.Spacing = input.Spacing;
                AdaptiveTextBlock textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
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
