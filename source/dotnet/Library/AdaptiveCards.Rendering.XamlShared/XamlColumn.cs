using System.Windows;
using System.Windows.Controls;

#if WPF

#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XamlColumn
    {
        public static FrameworkElement Render(Column column, RenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Column");

            XamlContainer.AddContainerElements(uiContainer, column.Items, context);

            if (column.SelectAction != null)
            {
                var uiButton = (Button)context.Render(column.SelectAction);//, new RenderContext(this.actionCallback, this.missingDataCallback));
                if (uiButton != null)
                {
                    uiButton.Content = uiContainer;
                    uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }

            return uiContainer;
        }
    }
}