// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
#if WPF
using System.Windows.Controls;
using System.Windows.Shapes;
using System.Windows.Media;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

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

#if WPF
            Border border = new Border();
            border.Child = uiColumnSet;
#elif XAMARIN
            Frame border = new Frame();
            //Xamarin default this to having a shadow
            //TODO: Confirm this on Xamarin Android
            border.HasShadow = false;
            border.Content = uiColumnSet;
#endif

            bool inheritsStyleFromParent = !columnSet.Style.HasValue;
            bool hasPadding = false;
            if (!inheritsStyleFromParent)
            {
#if WPF
                hasPadding = AdaptiveContainerRenderer.ApplyPadding(border, uiColumnSet, columnSet, parentRenderArgs, context);
#endif

                // Apply background color
                var columnSetStyle = context.Config.ContainerStyles.GetContainerStyleConfig(columnSet.Style);
#if WPF
                border.Background = context.GetColorBrush(columnSetStyle.BackgroundColor);
#endif
                childrenRenderArgs.ForegroundColors = columnSetStyle.ForegroundColors;
            }

            childrenRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : columnSet.Style.Value;

            for (int i = 0; i < columnSet.Columns.Count; ++i)
            {
                AdaptiveColumn column = columnSet.Columns[i];

                var childRenderArgs = new AdaptiveRenderArgs(childrenRenderArgs);
                // Reset up and down bleed for columns as that behaviour shouldn't be changed
                childRenderArgs.BleedDirection |= (BleedDirection.BleedUp | BleedDirection.BleedDown);

                if (i != 0)
                {
                    // Only the first column can bleed to the left
                    childRenderArgs.BleedDirection &= ~BleedDirection.BleedLeft;
                }

                if (i != columnSet.Columns.Count - 1)
                {
                    // Only the last column can bleed to the right
                    childRenderArgs.BleedDirection &= ~BleedDirection.BleedRight;
                }

                context.RenderArgs = childRenderArgs;

                FrameworkElement uiContainer = context.Render(column);

                // If the column couldn't be rendered and the fallback is 'drop'
                if (uiContainer != null)
                {
                    TagContent tag = null;

                    // Add vertical Separator
                    if (uiColumnSet.ColumnDefinitions.Count > 0 && (column.Separator || column.Spacing != AdaptiveSpacing.None))
                    {
                        var uiSep = new Grid();
                        uiSep.Style = context.GetStyle($"Adaptive.VerticalSeparator");

#if WPF
                    uiSep.VerticalAlignment = VerticalAlignment.Stretch;
#elif XAMARIN
                        // TOOD: check xamarin separator visual
                        //sep.VerticalAlignment = VerticalAlignment.Stretch;
#endif

                        int spacing = context.Config.GetSpacing(column.Spacing);
                        uiSep.Margin = new Thickness(spacing / 2.0, 0, spacing / 2.0, 0);

#if WPF
                        uiSep.Width = context.Config.Separator.LineThickness;
#endif
                        if (column.Separator && context.Config.Separator.LineColor != null)
                        {
#if WPF
                            uiSep.Background = context.GetColorBrush(context.Config.Separator.LineColor);
#elif XAMARIN
                            // TODO
#endif
                        }

                        tag = new TagContent(uiSep, uiColumnSet);

                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                        Grid.SetColumn(uiSep, uiColumnSet.ColumnDefinitions.Count - 1);
                        uiColumnSet.Children.Add(uiSep);
                    }
                    else
                    {
                        tag = new TagContent(null, uiColumnSet);
                    }

                    // do some sizing magic using the magic GridUnitType.Star
                    var width = column.Width?.ToLower();
                    if (string.IsNullOrEmpty(width))
#pragma warning disable CS0618 // Type or member is obsolete
                        width = column.Size?.ToLower();
#pragma warning restore CS0618 // Type or member is obsolete

                    ColumnDefinition columnDefinition = null;

                    if (width == null || width == AdaptiveColumnWidth.Stretch.ToLower())
                    {
                        columnDefinition = new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) };
                    }
                    else if (width == AdaptiveColumnWidth.Auto.ToLower())
                    {
                        columnDefinition = new ColumnDefinition() { Width = GridLength.Auto };
                    }
                    else
                    {
                        if (double.TryParse(width, out double val) && val >= 0)
                        {
                            // Weighted proportion (number only)
                            columnDefinition = new ColumnDefinition() { Width = new GridLength(val, GridUnitType.Star) };
                        }
                        else if (width.EndsWith("px") && double.TryParse(width.Substring(0, width.Length - 2), out double pxVal) && pxVal >= 0)
                        {
                            // Exact pixel (number followed by "px")
#if WPF
                            columnDefinition = new ColumnDefinition() { Width = new GridLength((int)pxVal, GridUnitType.Pixel) };
#endif
                        }
                        else
                        {
                            columnDefinition = new ColumnDefinition() { Width = GridLength.Auto };
                        }
                    }

                    // Store the column definition in the tag so we can toggle the visibility later
                    tag.ColumnDefinition = columnDefinition;
                    tag.ViewIndex = uiColumnSet.ColumnDefinitions.Count;

                    uiColumnSet.ColumnDefinitions.Add(columnDefinition);

#if WPF
                    uiContainer.Tag = tag;
#endif

                    Grid.SetColumn(uiContainer, uiColumnSet.ColumnDefinitions.Count - 1);
                    uiColumnSet.Children.Add(uiContainer);

                    context.SetVisibility(uiContainer, column.IsVisible, tag);
                }
            }

            context.ResetSeparatorVisibilityInsideContainer(uiColumnSet);

            // Revert context's value to that of outside the Container
            context.RenderArgs = parentRenderArgs;

#if WPF
            uiColumnSet.MinHeight = columnSet.PixelMinHeight;
#elif XAMARIN
            uiColumnSet.MinimumHeightRequest = columnSet.PixelMinHeight;
#endif

            return RendererUtil.ApplySelectAction(border, columnSet, context);
        }
    }
}
