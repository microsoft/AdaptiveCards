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
using FrameworkElement = Xamarin.Forms.View;
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public static partial class XamlActionSet 
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveActionSet actionSet = (AdaptiveActionSet)element;
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.ActionSet");

            AddActions(uiContainer, actionSet.Actions, context);

            return uiContainer;
        }
    }
}
