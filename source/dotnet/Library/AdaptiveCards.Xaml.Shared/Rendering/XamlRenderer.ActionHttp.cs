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
    public partial class XamlRenderer
    {
        public static FrameworkElement RenderActionHttp(TypedElement element, RenderContext context)
        {
            ActionHttp action = (ActionHttp)element;
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                Button uiButton = CreateActionButton(action, context);
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