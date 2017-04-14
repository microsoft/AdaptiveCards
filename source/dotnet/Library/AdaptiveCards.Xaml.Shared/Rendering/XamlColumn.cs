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
using AsNum.XFControls;
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public class XamlColumn : Column, IRender<FrameworkElement, RenderContext>
    {
        public FrameworkElement Render(RenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Column");

            XamlContainer.AddContainerElements(uiContainer, this.Items, context);

            if (this.SelectAction != null)
            {
                var uiButton = (Button)context.Render(this.SelectAction);//, new RenderContext(this.actionCallback, this.missingDataCallback));
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