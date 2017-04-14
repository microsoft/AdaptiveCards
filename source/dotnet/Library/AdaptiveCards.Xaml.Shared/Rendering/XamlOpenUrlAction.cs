using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{

    public class XamlOpenUrlAction : OpenUrlAction, IRender<FrameworkElement, RenderContext>
    {
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(this, context); // content);
                uiButton.Click += (sender, e) =>
                {
                    context.Action(uiButton, new ActionEventArgs() { Action = this});
                };
                return uiButton;
            }
            return null;
        }
    }
}