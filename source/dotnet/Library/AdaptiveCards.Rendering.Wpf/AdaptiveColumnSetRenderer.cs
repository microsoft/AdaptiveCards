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
            // This is the renderArgs that will be the base for all the columns renderArgs
            var childrenRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

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
                childrenRenderArgs.ForegroundColors = columnSetStyle.ForegroundColors;
            }

            childrenRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : columnSet.Style.Value;
            
            for (int i = 0; i < columnSet.Columns.Count; ++i)
            {
                AdaptiveColumn column = columnSet.Columns[i];

                var childRenderArgs = new AdaptiveRenderArgs(childrenRenderArgs);

                if (hasPadding)
                {
                    if (columnSet.Columns.Count == 1)
                    {
                        childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
                        childRenderArgs.BleedDirection = BleedDirection.Both;
                    }
                    else
                    {
                        if (i == 0)
                        {
                            childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
                            childRenderArgs.BleedDirection = BleedDirection.Left;
                        }
                        else if (i == (columnSet.Columns.Count - 1))
                        {
                            childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
                            childRenderArgs.BleedDirection = BleedDirection.Right;
                        }
                        else
                        {
                            childRenderArgs.BleedDirection = BleedDirection.None;
                        }
                    }
                }
                else
                {
                    if (columnSet.Columns.Count == 1)
                    {
                        childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
                        childRenderArgs.BleedDirection = parentRenderArgs.BleedDirection;
                    }
                    else
                    {
                        if (i == 0 &&
                            (childRenderArgs.BleedDirection == BleedDirection.Left || childRenderArgs.BleedDirection == BleedDirection.Both))
                        {
                            childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
                            childRenderArgs.BleedDirection = BleedDirection.Left;
                        }
                        else if (i == (columnSet.Columns.Count - 1) &&
                            (childRenderArgs.BleedDirection == BleedDirection.Right || childRenderArgs.BleedDirection == BleedDirection.Both))
                        {
                            childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
                            childRenderArgs.BleedDirection = BleedDirection.Right;
                        }
                        else
                        {
                            childRenderArgs.BleedDirection = BleedDirection.None;
                        }
                    }
                }

                context.RenderArgs = childRenderArgs;

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
