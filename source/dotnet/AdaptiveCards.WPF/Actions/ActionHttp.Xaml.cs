using System.Windows;
#if WPF
using System.Windows.Controls;
using WPF = System.Windows.Controls;
#elif Xamarin
using Xamarin.Forms;
using Button = AdaptiveCards.XamarinForms.Renderer.ContentButton;

#endif
using Newtonsoft.Json.Linq;
using System;
using System.Linq;

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// HttpAction
        /// </summary>
        /// <param name="httpAction"></param>
        /// <returns></returns>

        protected override FrameworkElement Render(ActionHttp action, RenderContext context)
        {
            if (this.Options.SupportInteraction)
            {
                Button uiButton = this.CreateActionButton(action, context);
                uiButton.Click += (sender, e) =>
                {
                    dynamic data = new JObject();
                    try
                    {

                        data = context.MergeInputData(data);

                        string body = (string)action.Body?.ToString() ?? String.Empty;

                        context.Action(uiButton, new ActionEventArgs()
                        {
                            Action = new ActionHttp()
                            {
                                Title = action.Title,
                                Method = action.Method,
                                Url = RendererUtilities.BindData(data, action.Url, url: true),
                                Headers = action.Headers,
                                Body = RendererUtilities.BindData(data, body),
                            },
                            Data = data
                        });
                    }
                    catch (MissingInputException err)
                    {
                        context.MissingInput(action, new MissingInputEventArgs(err.Input, err.FrameworkElement));
                    }
                };
                return uiButton;
            }
            return null;
        }

    }
}