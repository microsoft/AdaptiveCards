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

    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// OpenUrl
        /// </summary>
        /// <param name="openUrlAction"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(ActionOpenUrl action, RenderContext context)
        {
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                Button uiButton = this.CreateActionButton(action, context); // content);
                uiButton.Click += (sender, e) =>
                {
                    context.Action(uiButton, new ActionEventArgs() { Action = action });
                };
                return uiButton;
            }
            return null;
        }
    }
}