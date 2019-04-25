using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveColumnSetRenderer
    {
        public static FrameworkElement Render(AdaptiveColumnSet columnSet, AdaptiveRenderContext context)
        {
            var uiColumnSet = new Grid();
            uiColumnSet.Style = context.GetStyle($"Adaptive.{columnSet.Type}");

            // Keep track of ContainerStyle.ForegroundColors before Container is rendered
            var parentRenderArgs = context.RenderArgs;
            var elementRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            Border border = new Border();
            border.Child = uiColumnSet;

            bool inheritsStyleFromParent = !columnSet.Style.HasValue;
            bool hasPadding = false;
            if (!inheritsStyleFromParent)
            {
                hasPadding = AdaptiveContainerRenderer.ApplyPadding(border, uiColumnSet, columnSet, parentRenderArgs, context);

                // Apply background color
                var columnSetStyle = context.Config.ContainerStyles.GetContainerStyleConfig(columnSet.Style);

                border.Background = context.GetColorBrush(columnSetStyle.BackgroundColor);
                elementRenderArgs.ForegroundColors = columnSetStyle.ForegroundColors;
            }

            elementRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : columnSet.Style.Value;
            elementRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
            
            for (int i = 0; i < columnSet.Columns.Count; ++i)
            {
                AdaptiveColumn column = columnSet.Columns[i];

                var columnRenderArgs = new AdaptiveRenderArgs(elementRenderArgs);
                if (columnSet.Columns.Count == 1)
                {
                    columnRenderArgs.ColumnRelativePosition = ColumnPositionEnum.Only;
                }
                else
                {
                    if (i == 0)
                    {
                        columnRenderArgs.ColumnRelativePosition = ColumnPositionEnum.Begin;
                    }
                    else if (i == (columnSet.Columns.Count - 1))
                    {
                        columnRenderArgs.ColumnRelativePosition = ColumnPositionEnum.End;
                    }
                    else
                    {
                        columnRenderArgs.ColumnRelativePosition = ColumnPositionEnum.Intermediate;
                    }
                }
                context.RenderArgs = columnRenderArgs;

                FrameworkElement uiContainer = context.Render(column);

                // Add vertical Seperator
                if (uiColumnSet.ColumnDefinitions.Count > 0)
                {
                    if (column.Separator || column.Spacing != AdaptiveSpacing.None)
                    {

                        var uiSep = new Grid();
                        uiSep.Style = context.GetStyle($"Adaptive.VerticalSeparator");

                        uiSep.VerticalAlignment = VerticalAlignment.Stretch;

                        int spacing = context.Config.GetSpacing(column.Spacing);
                        uiSep.Margin = new Thickness(spacing / 2.0, 0, spacing / 2.0, 0);

                        uiSep.Width = context.Config.Separator.LineThickness;
                        if (column.Separator && context.Config.Separator.LineColor != null)
                            uiSep.Background = context.GetColorBrush(context.Config.Separator.LineColor);

                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                        Grid.SetColumn(uiSep, uiColumnSet.ColumnDefinitions.Count - 1);
                        uiColumnSet.Children.Add(uiSep);
                    }

                }

                // do some sizing magic using the magic GridUnitType.Star
                var width = column.Width?.ToLower();
                if (string.IsNullOrEmpty(width))
#pragma warning disable CS0618 // Type or member is obsolete
                    width = column.Size?.ToLower();
#pragma warning restore CS0618 // Type or member is obsolete
                if (width == null || width == AdaptiveColumnWidth.Stretch.ToLower())
                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                else if (width == AdaptiveColumnWidth.Auto.ToLower())
                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                else
                {
                    if (double.TryParse(width, out double val) && val >= 0)
                        // Weighted proportion (number only)
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(val, GridUnitType.Star) });
                    else if (width.EndsWith("px") && double.TryParse(width.Substring(0, width.Length-2), out double pxVal) && pxVal >= 0)
                        // Exact pixel (number followed by "px")
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength((int)pxVal, GridUnitType.Pixel) });
                    else
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                }

                Grid.SetColumn(uiContainer, uiColumnSet.ColumnDefinitions.Count - 1);
                uiColumnSet.Children.Add(uiContainer);
            }

            if (columnSet.SelectAction != null)
            {
                return context.RenderSelectAction(columnSet.SelectAction, border);
            }

            if(!columnSet.IsVisible)
            {
                uiColumnSet.Visibility = Visibility.Collapsed;
            }

            // Revert context's value to that of outside the Container
            context.RenderArgs = parentRenderArgs;

            return border;
        }
    }
}
