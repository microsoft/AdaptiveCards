using System.Windows;
#if WPF
using System.Windows.Controls;
using WPF = System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif
using Newtonsoft.Json.Linq;
using System;
using AdaptiveCards.Rendering;

namespace AdaptiveCards.Rendering
{
    public class XamlHttpAction : HttpAction, IRender<FrameworkElement, RenderContext>
    {
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(this, context);
                uiButton.Click += (sender, e) =>
                {
                    dynamic data = new JObject();
                    try
                    {

                        data = context.MergeInputData(data);

                        string body = (string)this.Body?.ToString() ?? String.Empty;

                        context.Action(uiButton, new ActionEventArgs()
                        {
                            Action = new HttpAction()
                            {
                                Title = this.Title,
                                Method = this.Method,
                                Url = RendererUtilities.BindData(data, this.Url, url: true),
                                Headers = this.Headers,
                                Body = RendererUtilities.BindData(data, body),
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
            return null;
        }

    }
}