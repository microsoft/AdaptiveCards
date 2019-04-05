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
            var parentRenderArgs = context.RenderArgs;
            var elementRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            Border border = new Border();
            border.Child = uiContainer;

            bool inheritsStyleFromParent = !column.Style.HasValue;
            bool columnHasPadding = false;

            if (!inheritsStyleFromParent)
            {
                columnHasPadding = AdaptiveContainerRenderer.ApplyPadding(border, uiContainer, column, parentRenderArgs, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(column.Style);
                border.Background = context.GetColorBrush(containerStyle.BackgroundColor);

                elementRenderArgs.ForegroundColors = containerStyle.ForegroundColors;
            }

            elementRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : column.Style.Value;
            if ((parentRenderArgs.ColumnRelativePosition == ColumnPositionEnum.Begin) ||
                (parentRenderArgs.ColumnRelativePosition == ColumnPositionEnum.End))
            {
                elementRenderArgs.ColumnRelativePosition = ColumnPositionEnum.Intermediate;
            }

            elementRenderArgs.HasParentWithPadding = columnHasPadding;
            context.RenderArgs = elementRenderArgs;

            AdaptiveContainerRenderer.AddContainerElements(uiContainer, column.Items, context);

            RendererUtil.ApplyVerticalContentAlignment(uiContainer, column);
            RendererUtil.ApplyIsVisible(uiContainer, column);
            RendererUtil.ApplyMinHeight(uiContainer, column);
            
            // Revert context's value to that of outside the Column
            context.RenderArgs = parentRenderArgs;

            return RendererUtil.ApplySelectAction(border, column, context);
        }
    }
}
