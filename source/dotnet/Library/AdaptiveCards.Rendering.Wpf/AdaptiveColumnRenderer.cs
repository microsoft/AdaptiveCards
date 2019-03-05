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

            Border border = new Border();
            border.Child = uiContainer;

            bool inheritsStyleFromParent = (column.Style == AdaptiveContainerStyle.None);

            if (!inheritsStyleFromParent)
            {
                AdaptiveContainerRenderer.ApplyPadding(border, uiContainer, column, parentContainerStyle, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(column.Style);
                border.Background = context.GetColorBrush(containerStyle.BackgroundColor);

                context.ForegroundColors = containerStyle.ForegroundColors;
            }

            context.ParentStyle = (inheritsStyleFromParent) ? parentContainerStyle : column.Style;

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

            return border;
        }
    }
}
