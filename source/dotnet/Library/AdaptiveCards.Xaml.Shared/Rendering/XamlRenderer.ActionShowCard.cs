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
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// ShowCard
        /// </summary>
        /// <param name="showCardAction"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(ActionShowCard action, RenderContext context)
        {

            if (this.Options.SupportInteraction)
            {
                Button uiButton = this.CreateActionButton(action, context);
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