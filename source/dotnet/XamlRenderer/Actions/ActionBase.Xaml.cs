using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;

namespace Adaptive
{

    public partial class ActionBase
    {
        protected Button CreateActionButton(RenderContext renderContext)
        {
            var uiButton = new Button();
            WPF.TextBlock uiTitle = new WPF.TextBlock() { Text = this.Title };
            uiTitle.Style = renderContext.GetStyle($"Adaptive.Action.Title");
            uiButton.Content = uiTitle;
            string name = this.GetType().Name.Replace("Action", String.Empty);
            uiButton.Style = renderContext.GetStyle($"Adaptive.Action.{name}");
            return uiButton;
        }
    }
}