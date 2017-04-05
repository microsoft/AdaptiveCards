using System;
using System.Linq;
using System.Windows;
#if WPF
using System.Windows.Controls;
using xaml = System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{

    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {

        protected Button CreateActionButton(ActionBase action, RenderContext renderContext)
        {
#if WPF
            ActionStyling styling = renderContext.Styling.GetActionStyling(action);
            var uiButton = new Button()
            {
                Background = this.GetColorBrush(styling.BackgroundColor),
                Margin = (styling.Margin.Length == 4) ? 
                            new Thickness(styling.Margin[0], styling.Margin[1], styling.Margin[2], styling.Margin[3]) :
                            new Thickness(styling.Margin.First()),
                HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch,
                BorderBrush = this.GetColorBrush(styling.BorderColor)
            };
            uiButton.Style = this.GetStyle($"Adaptive.{action.Type}");

            xaml.TextBlock uiTitle = new xaml.TextBlock()
            {
                Text = action.Title,
                FontWeight = FontWeight.FromOpenTypeWeight(styling.FontWeight),
                FontSize = styling.FontSize,
                Foreground = this.GetColorBrush(styling.TextColor),
                Margin = (styling.TitleMargin.Length == 4) ?
                            new Thickness(styling.TitleMargin[0], styling.TitleMargin[1], styling.TitleMargin[2], styling.TitleMargin[3]) :
                            new Thickness(styling.TitleMargin.First()),
            };
            uiTitle.Style = this.GetStyle($"Adaptive.Action.Title");
            uiButton.Content = uiTitle;
            string name = this.GetType().Name.Replace("Action", String.Empty);
            return uiButton;

#elif XAMARIN
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