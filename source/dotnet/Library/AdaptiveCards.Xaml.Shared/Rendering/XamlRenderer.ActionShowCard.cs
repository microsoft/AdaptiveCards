using System;
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
    public partial class XamlRenderer
    {
        public static FrameworkElement RenderActionShowCard(TypedElement element, RenderContext context)
        {
            ShowCardAction action = (ShowCardAction)element;

            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                Button uiButton = CreateActionButton(action, context);
                uiButton.Click += (sender, e) =>
                {
                    context.Action(uiButton, new ActionEventArgs() { Action = action, Data = null });
                };
                return uiButton;
            }
            return null;
        }
    }
}