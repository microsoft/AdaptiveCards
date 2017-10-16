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

    public static class XamlOpenUrlAction
    {
        public static FrameworkElement Render(OpenUrlAction action, RenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(action, context); // content);
                uiButton.Click += (sender, e) =>
                {
                    context.Action(uiButton, new AdaptiveActionEventArgs() { Action = action});
                };
                return uiButton;
            }
            return null;
        }
    }
}