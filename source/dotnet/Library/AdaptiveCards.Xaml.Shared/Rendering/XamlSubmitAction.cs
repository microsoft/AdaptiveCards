using Newtonsoft.Json.Linq;
using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlSubmitAction
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            SubmitAction action = (SubmitAction)element;
            if (context.Options.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(action, context); // content
                uiButton.Click += (sender, e) =>
                {
                    try
                    {

                        dynamic data = (action.Data != null) ? ((JToken)action.Data).DeepClone() : new JObject();
                        data = context.MergeInputData(data);
                        context.Action(uiButton, new ActionEventArgs() { Action = action, Data = data });
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