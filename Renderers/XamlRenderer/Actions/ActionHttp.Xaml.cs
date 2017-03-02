using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;
using System.Linq;

namespace Adaptive
{


    public partial class ActionHttp : ActionBase
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<ActionHttp, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// HttpAction
        /// </summary>
        /// <param name="httpAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            Button uiButton = this.CreateActionButton(context);
            uiButton.Click += (sender, e) =>
            {
                dynamic data = new JObject();
                try
                {

                    data = context.MergeInputData(data);

                    string body = (string)this.Body?.ToString() ?? String.Empty;

                    context.Action(uiButton, new ActionEventArgs()
                    {
                        Action = new ActionHttp()
                        {
                            Title = this.Title,
                            Method = this.Method,
                            Url = Utilities.BindData(data, this.Url, url: true),
                            Headers = this.Headers,
                            Body = Utilities.BindData(data, body),
                        },
                        Data = data
                    });
                }
                catch (MissingInputException err)
                {
                    context.MissingInput(this, new MissingInputEventArgs(err.Input, err.FrameworkElement));
                }
            };
            return uiButton;
        }

    }
}