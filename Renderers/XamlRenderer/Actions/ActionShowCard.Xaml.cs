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
        /// ShowCard
        /// </summary>
        /// <param name="showCardAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context) // , FrameworkElement content)
        {
            Button uiButton = this.CreateActionButton(context);
            uiButton.Click += (sender, e) =>
            {
                context.Invoke(uiButton, new ActionEventArgs() { Action = this, Data = null });
            };
            return uiButton;
        }
    }
}