using System.Windows;
using System.Windows.Controls;
using Newtonsoft.Json.Linq;

#if WPF

#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XamlSubmitAction
    {
        public static FrameworkElement Render(AdaptiveSubmitAction action, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(action, context); // content
                uiButton.Click += (sender, e) =>
                {
                    try
                    {

                        dynamic data = (action.Data != null) ? ((JToken)action.Data).DeepClone() : new JObject();
                        data = context.MergeInputData(data);
                        context.Action(uiButton, new AdaptiveActionEventArgs() { Action = action, Data = data });
                    }
                    catch (MissingInputException err)
                    {
                        context.MissingInput(action, new MissingInputEventArgs(err.AdaptiveInput, err.FrameworkElement));
                    }
                };
                return uiButton;
            }
            return null;
        }
    }
}