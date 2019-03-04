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
            uiContainer.SetBackgroundSource(column.BackgroundImage, context);

            // Keep track of ContainerStyle.ForegroundColors before Container is rendered
            var outerStyle = context.ForegroundColors;
            var parentContainerStyle = context.ParentStyle;
           
            if (column.Style != null)
            {
                AdaptiveContainerRenderer.ApplyPadding(uiContainer, column, parentContainerStyle, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(column.Style);
                uiContainer.SetBackgroundColor(containerStyle.BackgroundColor, context);

                context.ForegroundColors = containerStyle.ForegroundColors;
            }

            AdaptiveContainerStyle containerContainerStyle = column.Style ?? parentContainerStyle;
            if (containerContainerStyle == AdaptiveContainerStyle.None)
            {
                containerContainerStyle = parentContainerStyle;
            }
            context.ParentStyle = containerContainerStyle;

            AdaptiveContainerRenderer.AddContainerElements(uiContainer, column.Items, context);

            if (column.SelectAction != null)
            {
                return context.RenderSelectAction(column.SelectAction, uiContainer);
            }

            switch(column.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
                    uiContainer.VerticalAlignment = VerticalAlignment.Center;
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    uiContainer.VerticalAlignment = VerticalAlignment.Bottom;
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    break;
            }

            if(!column.IsVisible)
            {
                uiContainer.Visibility = Visibility.Collapsed;
            }

            // Revert context's value to that of outside the Column
            context.ForegroundColors = outerStyle;
            context.ParentStyle = parentContainerStyle;

            return uiContainer;
        }
    }
}
