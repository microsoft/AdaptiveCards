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
    public class XamlSubmitAction : SubmitAction, IRender<FrameworkElement, RenderContext>
    {
        public FrameworkElement Render(RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                Button uiButton = XamlUtilities.CreateActionButton(this, context); // content
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