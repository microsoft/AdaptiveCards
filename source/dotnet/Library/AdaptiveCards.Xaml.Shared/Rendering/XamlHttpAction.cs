using System.Windows;
#if WPF
using System.Windows.Controls;
using WPF = System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
using FrameworkElement = Xamarin.Forms.View;
#endif
using Newtonsoft.Json.Linq;
using System;
using AdaptiveCards.Rendering;

namespace AdaptiveCards.Rendering
{
    public static class XamlHttpAction
    {
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            HttpAction action = (HttpAction)element;
            if (context.Config.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(action, context);
                uiButton.Click += (sender, e) =>
                {
                    dynamic data = new JObject();
                    try
                    {

                        data = context.MergeInputData(data);

                        string body = (string)action.Body?.ToString() ?? String.Empty;

                        context.Action(uiButton, new ActionEventArgs()
                        {
                            Action = new HttpAction()
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
