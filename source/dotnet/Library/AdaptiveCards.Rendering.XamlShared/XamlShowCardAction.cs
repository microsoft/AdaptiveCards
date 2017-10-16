using System.Windows;
using System.Windows.Controls;

#if WPF

#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XamlShowCardAction
    {
        public static FrameworkElement Render(ShowCardAction action, RenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(action, context);
                uiButton.Click += (sender, e) =>
                {
                    context.Action(uiButton, new AdaptiveActionEventArgs() { Action = action, Data = null });
                };
                return uiButton;
            }
            return null;
        }
    }
}