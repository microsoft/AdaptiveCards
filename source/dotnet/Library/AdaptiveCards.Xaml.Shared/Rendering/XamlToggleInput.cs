using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public class XamlToggleInput : ToggleInput, IRender<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
#if WPF
                var uiToggle = new CheckBox();
                uiToggle.Content = this.Title;
                uiToggle.IsChecked = this.Value == (this.ValueOn ?? "true");
                uiToggle.Style = context.GetStyle($"Adaptive.this.Toggle");
                uiToggle.DataContext = this;
                context.InputBindings.Add(this.Id, () =>
                {
                    return uiToggle.IsChecked == true ? this.ValueOn ?? "true" : this.ValueOff ?? "false";
                });
                return uiToggle;
#elif XAMARIN
                var uiToggle = new Switch();
                // TODO: Finish switch
                //uiToggle.Content = this.Title;
                uiToggle.IsToggled = this.Value == (this.ValueOn ?? "true");
                uiToggle.Style = context.GetStyle($"Adaptive.this.Toggle");
                uiToggle.BindingContext = this;
                context.InputBindings.Add(this.Id, () =>
                {
                    return uiToggle.IsToggled == true ? this.ValueOn ?? "true" : this.ValueOff ?? "false";
                });
                return uiToggle;
#endif
            }
            else
            {
                Container container = TypedElementConverter.CreateElement<Container>();
                container.Separation = this.Separation;

                TextBlock textBlock = TypedElementConverter.CreateElement<TextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(this);
                container.Items.Add(textBlock);
                if (this.Value != null)
                {
                    textBlock = TypedElementConverter.CreateElement<TextBlock>();
                    textBlock.Text = (this.Value == (this.ValueOn ?? "true")) ? this.ValueOn ?? "selected" : this.ValueOff ?? "not selected";
                    textBlock.Color = TextColor.Accent;
                    textBlock.Wrap = true;
                    container.Items.Add(textBlock);
                }
                return context.Render(container);
            }

        }
    }

}