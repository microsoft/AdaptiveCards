using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;

namespace Adaptive
{
    public partial class ActionShowCard
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<ActionShowCard, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// ShowCard
        /// </summary>
        /// <param name="showCardAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context) // , FrameworkElement content)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            if (context.Options.SupportInteraction)
            {
                Button uiButton = this.CreateActionButton(context);
                uiButton.Click += (sender, e) =>
                {
                    context.Action(uiButton, new ActionEventArgs() { Action = this, Data = null });
                };
                return uiButton;
            }
            return null;
        }
    }
}