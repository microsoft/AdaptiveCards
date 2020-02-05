using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using FrameworkElement = Xamarin.Forms.View;
using Xamarin.Forms;
using CheckBox = Xamarin.Forms.Switch;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlToggleInput
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveToggleInput input = (AdaptiveToggleInput)element;
            if (context.Config.SupportsInteractivity)
            {
                var uiToggle = new CheckBox();
#if WPF
                // TODO: Finish switch
                uiToggle.Content = input.Title;
#endif
                uiToggle.SetState(input.Value == (input.ValueOn ?? "true"));
                uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");
                uiToggle.SetContext(input);
                context.InputBindings.Add(input.Id, () =>
                {
                    return uiToggle.GetState() == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false";
                });
                return uiToggle;
            }
            else
            {
                AdaptiveContainer container = AdaptiveTypedElementConverter.CreateElement<AdaptiveContainer>();
                container.Separator = input.Separator;
                container.Spacing = input.Spacing;

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
