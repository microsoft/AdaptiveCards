using System;
using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlShowCardAction
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            ShowCardAction action = (ShowCardAction)element;
            if (context.Options.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(action, context);
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