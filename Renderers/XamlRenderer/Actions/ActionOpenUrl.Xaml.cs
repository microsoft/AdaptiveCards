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
        /// OpenUrl
        /// </summary>
        /// <param name="openUrlAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context) // content);
        {
            Button uiButton = this.CreateActionButton(context); // content);
            uiButton.Click += (sender, e) =>
            {
                context.Invoke(uiButton, new ActionEventArgs() { Action = this });
            };
            return uiButton;
        }
    }
}