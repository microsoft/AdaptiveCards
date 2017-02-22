using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;

namespace Adaptive
{
    public partial class ActionSubmit
    {
        /// <summary>
        /// SubmitAction
        /// </summary>
        /// <param name="submitAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            Button uiButton = this.CreateActionButton(context); // content
            uiButton.Click += (sender, e) =>
            {
                dynamic data = (this.Data != null) ? ((JToken)this.Data).DeepClone() : new JObject();
                data = context.MergeInputData(data);
                context.Invoke(uiButton, new ActionEventArgs() { Action = this, Data = data });
            };
            return uiButton;
        }
    }
}