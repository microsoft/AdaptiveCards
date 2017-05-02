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
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            ToggleInput input = (ToggleInput)element;
            if (context.Config.SupportsInteractivity)
            {
                var uiToggle = new CheckBox();
#if WPF
                // TODO: Finish switch
                uiToggle.Content = input.Title;
#endif
                uiToggle.SetState(input.Value == (input.ValueOn ?? "true"));
                uiToggle.Style = context.GetStyle($"Adaptive.input.Toggle");
                uiToggle.SetContext(input);
                context.InputBindings.Add(input.Id, () =>
                {
                    return uiToggle.GetState() == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false";
                });
                return uiToggle;
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