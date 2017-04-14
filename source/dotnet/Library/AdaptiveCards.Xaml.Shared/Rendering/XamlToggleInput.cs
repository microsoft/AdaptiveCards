using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlToggleInput
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            ToggleInput input = (ToggleInput)element;
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
#if WPF
                var uiToggle = new CheckBox();
                uiToggle.Content = input.Title;
                uiToggle.IsChecked = input.Value == (input.ValueOn ?? "true");
                uiToggle.Style = context.GetStyle($"Adaptive.input.Toggle");
                uiToggle.DataContext = input;
                context.InputBindings.Add(input.Id, () =>
                {
                    return uiToggle.IsChecked == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false";
                });
                return uiToggle;
#elif XAMARIN
                var uiToggle = new Switch();
                // TODO: Finish switch
                //uiToggle.Content = input.Title;
                uiToggle.IsToggled = input.Value == (input.ValueOn ?? "true");
                uiToggle.Style = context.GetStyle($"Adaptive.input.Toggle");
                uiToggle.BindingContext = input;
                context.InputBindings.Add(input.Id, () =>
                {
                    return uiToggle.IsToggled == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false";
                });
                return uiToggle;
#endif
            }
            else
            {
                Container container = TypedElementConverter.CreateElement<Container>();
                container.Separation = input.Separation;

                TextBlock textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input);
                container.Items.Add(textBlock);
                if (input.Value != null)
                {
                    textBlock = TypedElementConverter.CreateElement<TextBlock>();
                    textBlock.Text = (input.Value == (input.ValueOn ?? "true")) ? input.ValueOn ?? "selected" : input.ValueOff ?? "not selected";
                    textBlock.Color = TextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }

        }
    }

}