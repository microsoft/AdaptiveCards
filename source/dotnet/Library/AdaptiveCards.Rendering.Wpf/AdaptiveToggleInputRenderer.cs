using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveToggleInputRenderer
    {
        public static FrameworkElement Render(AdaptiveToggleInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var uiToggle = new CheckBox();

                uiToggle.Content = input.Title;
                uiToggle.SetState(input.Value == (input.ValueOn ?? "true"));
                uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");
                uiToggle.SetContext(input);
                context.InputBindings.Add(input.Id, () => uiToggle.GetState() == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false");
                return uiToggle;
            }
            else
            {
                AdaptiveContainer container = AdaptiveTypedElementConverter.CreateElement<AdaptiveContainer>();
                container.Spacing = input.Spacing;
                container.Separator = input.Separator;

                AdaptiveTextBlock textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input);
                container.Items.Add(textBlock);
                if (input.Value != null)
                {
                    textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                    textBlock.Text = (input.Value == (input.ValueOn ?? "true")) ? input.ValueOn ?? "selected" : input.ValueOff ?? "not selected";
                    textBlock.Color = AdaptiveTextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }

        }
    }

}