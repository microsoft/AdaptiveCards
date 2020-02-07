using System.Collections.Generic;
using System.Linq;
using System.Windows;
using AdaptiveCards.Rendering;
using System;
#if WPF
using System.Windows.Shapes;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlColumn
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveColumn column = (AdaptiveColumn)element;
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Column");

            AdaptiveContainerRenderer.AddContainerElements(uiContainer, column.Items, context);

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
