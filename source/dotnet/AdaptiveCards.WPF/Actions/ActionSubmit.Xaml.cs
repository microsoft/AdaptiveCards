using Newtonsoft.Json.Linq;
using System.Windows;
#if WPF
using System.Windows.Controls;
#elif Xamarin
using Xamarin.Forms;
using Button = AdaptiveCards.XamarinForms.Renderer.ContentButton;
#endif

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// SubmitAction
        /// </summary>
        /// <param name="submitAction"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(ActionSubmit action, RenderContext context)
        {

            if (this.Options.SupportInteraction)
            {
                Button uiButton = this.CreateActionButton(action, context); // content
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