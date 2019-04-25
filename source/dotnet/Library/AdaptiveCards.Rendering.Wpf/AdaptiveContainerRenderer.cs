using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveContainerRenderer
    {
        public static FrameworkElement Render(AdaptiveContainer container, AdaptiveRenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Container");
            uiContainer.SetBackgroundSource(container.BackgroundImage, context);

            // Keep track of ContainerStyle.ForegroundColors before Container is rendered
            var parentRenderArgs = context.RenderArgs;
            // This is the renderArgs that will be passed down to the children
            var childRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);
            
            Grid uiOuterContainer = new Grid();
            
            uiOuterContainer.Children.Add(uiContainer);
            Border border = new Border();
            border.Child = uiOuterContainer;

            RendererUtil.ApplyVerticalContentAlignment(uiContainer, container);
            uiContainer.MinHeight = container.PixelMinHeight;

            bool inheritsStyleFromParent = !container.Style.HasValue;
            bool hasPadding = false;
            if (!inheritsStyleFromParent)
            {
                hasPadding = ApplyPadding(border, uiOuterContainer, container, parentRenderArgs, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(container.Style);
                border.Background = context.GetColorBrush(containerStyle.BackgroundColor);

                childRenderArgs.ForegroundColors = containerStyle.ForegroundColors;
            }

            switch (container.VerticalContentAlignment)
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

            if (hasPadding)
            {
                childRenderArgs.BleedDirection = BleedDirection.Both;
            }

            // Modify context outer parent style so padding necessity can be determined
            childRenderArgs.ParentStyle = (inheritsStyleFromParent) ? parentRenderArgs.ParentStyle : container.Style.Value;
            childRenderArgs.HasParentWithPadding = (hasPadding || parentRenderArgs.HasParentWithPadding);
            context.RenderArgs = childRenderArgs;

            AddContainerElements(uiContainer, container.Items, context);

            // Revert context's value to that of outside the Container
            context.RenderArgs = parentRenderArgs;

            return RendererUtil.ApplySelectAction(border, container, context);
        }

        public static void AddContainerElements(Grid uiContainer, IList<AdaptiveElement> elements, AdaptiveRenderContext context)
        {
            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = context.Render(cardElement);
                if (uiElement != null)
                {
                    TagContent tag = new TagContent(AdaptiveSpacing.None, uiContainer);

                    if (cardElement.Separator && uiContainer.Children.Count > 0)
                    {
                        Grid separator = AddSeparator(context, cardElement, uiContainer);
                        tag = new TagContent(separator, uiContainer);
                    }
                    else if (uiContainer.Children.Count > 0)
                    {
                        var spacing = context.Config.GetSpacing(cardElement.Spacing);
                        Thickness renderedMargin = uiElement.Margin;
                        uiElement.Margin = new Thickness(renderedMargin.Left,
                                                         renderedMargin.Top + spacing,
                                                         renderedMargin.Right,
                                                         renderedMargin.Bottom);
                        tag = new TagContent(cardElement.Spacing, uiContainer);
                    }

                    uiElement.Tag = tag;

                    if (cardElement.Type == "Container" || cardElement.Type == "ColumnSet")
                    {
                        AdaptiveCollectionElement collectionElement = (AdaptiveCollectionElement)cardElement;
                        uiElement.MinHeight = collectionElement.PixelMinHeight;
                    }

                    if (cardElement.Height != AdaptiveHeight.Stretch)
                    {
                        context.SetVisibility(uiElement, cardElement.IsVisible, tag);
                        uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                        Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                        uiContainer.Children.Add(uiElement);
                    }
                    else
                    {
                        if (cardElement.Type == "Container")
                        {
                            context.SetVisibility(uiElement, cardElement.IsVisible, tag);
                            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
                            Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                            uiContainer.Children.Add(uiElement);
                        }
                        else
                        {
                            StackPanel panel = new StackPanel();
                            context.SetVisibility(panel, cardElement.IsVisible, tag);
                            if (!String.IsNullOrEmpty(cardElement.Id))
                            {
                                panel.Name = cardElement.Id;
                            }
                            panel.Children.Add(uiElement);

                            panel.Tag = tag;

                            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
                            Grid.SetRow(panel, uiContainer.RowDefinitions.Count - 1);
                            uiContainer.Children.Add(panel);
                        }
                    }

                }
            }

            context.ResetSeparatorVisibilityInsideContainer(uiContainer);
        }

        public static Grid AddSeparator(AdaptiveRenderContext context, AdaptiveElement element, Grid uiContainer)
        {
            if (element.Spacing == AdaptiveSpacing.None && !element.Separator)
                return null;

            var uiSep = new Grid();
            uiSep.Style = context.GetStyle($"Adaptive.Separator");
            int spacing = context.Config.GetSpacing(element.Spacing);

            SeparatorConfig sepStyle = context.Config.Separator;

            uiSep.Margin = new Thickness(0, (spacing - sepStyle.LineThickness) / 2, 0, 0);
            uiSep.SetHeight(sepStyle.LineThickness);
            if (!string.IsNullOrWhiteSpace(sepStyle.LineColor))
                uiSep.SetBackgroundColor(sepStyle.LineColor,context);
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiSep);

            return uiSep;
        }
        
        // For applying bleeding, we must know if the element has padding, so both properties are applied in the same method
        public static bool ApplyPadding(Border border, Grid uiElement, AdaptiveCollectionElement element, AdaptiveRenderArgs parentRenderArgs, AdaptiveRenderContext context)
        {
            bool canApplyPadding = false;

            // AdaptiveColumn inherits from AdaptiveContainer so only one check is required for both
            if (element is AdaptiveContainer container)
            {
                canApplyPadding = ((container.BackgroundImage != null) || (container.Style.HasValue && (container.Style != parentRenderArgs.ParentStyle)));
            }
            else if (element is AdaptiveColumnSet columnSet)
            {
                canApplyPadding = (columnSet.Style.HasValue && (columnSet.Style != parentRenderArgs.ParentStyle));
            }

            int padding = context.Config.Spacing.Padding;

            if (canApplyPadding)
            {
                uiElement.Margin = new Thickness { Left = padding, Top = padding, Right = padding, Bottom = padding };

                if (element.Bleed)
                {
                    int leftMargin = 0, rightMargin = 0;
                    if (parentRenderArgs.BleedDirection == BleedDirection.Left || parentRenderArgs.BleedDirection == BleedDirection.Both)
                    {
                        leftMargin = -padding;
                    }

                    if (parentRenderArgs.BleedDirection == BleedDirection.Right || parentRenderArgs.BleedDirection == BleedDirection.Both)
                    {
                        rightMargin = -padding;
                    }

                    border.Margin = new Thickness { Left = leftMargin, Right = rightMargin };
                }
            }

            return canApplyPadding;
        }
    }
}
