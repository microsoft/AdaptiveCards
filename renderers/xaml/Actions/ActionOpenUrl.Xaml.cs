using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;

namespace Adaptive
{

    public partial class ActionOpenUrl
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<ActionOpenUrl, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// OpenUrl
        /// </summary>
        /// <param name="openUrlAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context) // content);
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            Button uiButton = this.CreateActionButton(context); // content);
            uiButton.Click += (sender, e) =>
            {
                context.Action(uiButton, new ActionEventArgs() { Action = this });
            };
            return uiButton;
        }
    }
}