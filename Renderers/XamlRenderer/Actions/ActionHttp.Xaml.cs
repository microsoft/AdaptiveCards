using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;

namespace Adaptive
{


    public partial class ActionHttp : ActionBase
    {
        /// <summary>
        /// HttpAction
        /// </summary>
        /// <param name="httpAction"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            Button uiButton = this.CreateActionButton(context);
            uiButton.Click += (sender, e) =>
            {
                dynamic data = new JObject();
                data = context.MergeInputData(data);

                string body = (string)this.Body?.ToString() ?? String.Empty;

                context.Invoke(uiButton, new ActionEventArgs()
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
            };
            return uiButton;
        }

    }
}