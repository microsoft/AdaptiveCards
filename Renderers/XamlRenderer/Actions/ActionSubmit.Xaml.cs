using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;
using System.Linq;

namespace Adaptive
{
    public partial class ActionSubmit
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<ActionSubmit, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// SubmitAction
        /// </summary>
        /// <param name="submitAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            if (context.Options.SupportInteraction)
            {
                Button uiButton = this.CreateActionButton(context); // content
                uiButton.Click += (sender, e) =>
                {
                    try
                    {

                        dynamic data = (this.Data != null) ? ((JToken)this.Data).DeepClone() : new JObject();
                        data = context.MergeInputData(data);
                        context.Action(uiButton, new ActionEventArgs() { Action = this, Data = data });
                    }
                    catch (MissingInputException err)
                    {
                        context.MissingInput(this, new MissingInputEventArgs(err.Input, err.FrameworkElement));
                    }
                };
                return uiButton;
            }
            return null;
        }
    }
}