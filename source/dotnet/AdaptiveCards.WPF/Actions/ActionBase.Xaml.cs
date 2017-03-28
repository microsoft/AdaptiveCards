using System;
using System.Windows;
#if WPF
using System.Windows.Controls;
using xaml = System.Windows.Controls;
#elif Xamarin
using Xamarin.Forms;
using Button = AdaptiveCards.XamarinForms.Renderer.ContentButton;
#endif

namespace AdaptiveCards.Renderers
{

    public partial class XamlRenderer 
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {

        protected Button CreateActionButton(ActionBase action, RenderContext renderContext)
        {
#if WPF
            var uiButton = new Button();
            xaml.TextBlock uiTitle = new xaml.TextBlock() { Text = action.Title };
            uiTitle.Style = this.GetStyle($"Adaptive.Action.Title");
            uiButton.Content = uiTitle;
            string name = this.GetType().Name.Replace("Action", String.Empty);
            uiButton.Style = this.GetStyle($"Adaptive.Action.{name}");
            return uiButton;

#elif Xamarin
            var uiButton = new Button();
            // TODO: button styling
            uiButton.Text = action.Title;
            string name = this.GetType().Name.Replace("Action", String.Empty);
            uiButton.Style = this.GetStyle($"Adaptive.Action.{name}");
            return uiButton;
#endif
        }
    }
}