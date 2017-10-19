using System.Windows;
using System.Windows.Controls;


namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveColumnRenderer
    {
        public static FrameworkElement Render(AdaptiveColumn adaptiveColumn, AdaptiveRenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Column");

            AdaptiveContainerRenderer.AddContainerElements(uiContainer, adaptiveColumn.Items, context);

            if (adaptiveColumn.SelectAction != null)
            {
                var uiButton = (Button)context.Render(adaptiveColumn.SelectAction);//, new RenderContext(this.actionCallback, this.missingDataCallback));
                if (uiButton != null)
                {
                    uiButton.Content = uiContainer;
                    uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }

            return uiContainer;
        }
    }
}