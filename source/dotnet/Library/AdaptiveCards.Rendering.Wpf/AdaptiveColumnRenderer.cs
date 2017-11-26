using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;


namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveColumnRenderer
    {
        public static FrameworkElement Render(AdaptiveColumn column, AdaptiveRenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Column");

            AdaptiveContainerRenderer.AddContainerElements(uiContainer, column.Items, context);

            if (column.SelectAction != null)
            {
                return context.RenderSelectAction(column.SelectAction, uiContainer);
            }

            return uiContainer;
        }
    }
}