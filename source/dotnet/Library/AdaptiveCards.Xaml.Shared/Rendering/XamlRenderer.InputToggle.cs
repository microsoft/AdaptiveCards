using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
    {
        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected static FrameworkElement RenderInputToggle(TypedElement element, RenderContext context)
        {
            InputToggle input = (InputToggle)element;
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
#if WPF
                var uiToggle = new CheckBox();
                uiToggle.Content = input.Title;
                uiToggle.IsChecked = input.Value == (input.ValueOn ?? "true");
                uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");
                uiToggle.DataContext = input;
                context.InputControls.Add(uiToggle);
                return uiToggle;
#elif XAMARIN
                var uiToggle = new Switch();
                // TODO: Finish switch
                //uiToggle.Content = input.Title;
                uiToggle.IsToggled = input.Value == (input.ValueOn ?? "true");
                uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");
                uiToggle.BindingContext = input;
                context.InputControls.Add(uiToggle);
                return uiToggle;
#endif
            }
            else
            {
                Container container = new Container() { Separation = input.Separation };
                container.Items.Add(new TextBlock() { Text = GetFallbackText(input)});
                if (input.Value != null)
                {
                    container.Items.Add(new TextBlock()
                    {
                        Text = (input.Value == (input.ValueOn ?? "true")) ? input.ValueOn ?? "selected" : input.ValueOff ?? "not selected",
                        Color = TextColor.Accent,
                        Wrap = true
                    });
                }
                return context.Render(container);
            }

        }
    }

}