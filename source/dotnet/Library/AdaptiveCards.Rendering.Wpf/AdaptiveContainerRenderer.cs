using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveContainerRenderer
    {
        public static FrameworkElement Render(AdaptiveContainer container, AdaptiveRenderContext context)
        {
            var uiContainer = new Grid();
            //uiContainer.Margin = new Thickness(context.Config.Spacing.Padding);
            uiContainer.Style = context.GetStyle("Adaptive.Container");

            var parentContainerStyle = context.ContainerStyle;
            var thisContainerStyle = container.Style ?? parentContainerStyle;
            var parentDesiredMarginFromParent = context.DesiredMarginFromParent;
            context.ContainerStyle = thisContainerStyle;

            // If style is different, we need to apply background
            if (parentContainerStyle != thisContainerStyle)
            {
                uiContainer.SetBackgroundColor(context.Config.ContainerStyles.Get(thisContainerStyle).BackgroundColor, context);

                // And set desired margin for children
                context.DesiredMarginFromParent = new AdaptiveThickness(AdaptiveSpacing.Padding);
            }
            else
            {
                // Ensure no margin for children is added
                context.DesiredMarginFromParent = new AdaptiveThickness(AdaptiveSpacing.None);
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

            AddContainerElements(uiContainer, container.Items, context);

            if (container.SelectAction != null)
            {
                var renderedSelectAction = context.RenderSelectAction(container.SelectAction, uiContainer);
                context.ContainerStyle = parentContainerStyle;
                return renderedSelectAction;
            }

            Grid uiOuterContainer = new Grid();
            uiOuterContainer.Children.Add(uiContainer);
            Border border = new Border();
            border.Child = uiOuterContainer;
            context.ContainerStyle = parentContainerStyle;
            return border;
        }

        public static void AddContainerElements(Grid uiContainer, IList<AdaptiveElement> elements, AdaptiveRenderContext context)
        {
            var parentDesiredMarginFromParent = context.DesiredMarginFromParent;
            List<Tuple<AdaptiveElement, FrameworkElement>> renderedElements = new List<Tuple<AdaptiveElement, FrameworkElement>>();

            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = context.Render(cardElement);
                if (uiElement != null)
                {
                    if (cardElement.Separator && uiContainer.Children.Count > 0)
                    {
                        AddSeperator(context, cardElement, uiContainer);
                    }
                    else if (uiContainer.Children.Count > 0)
                    {
                        var spacing = context.Config.GetSpacing(cardElement.Spacing);
                        uiElement.Margin = new Thickness(0, spacing, 0, 0);
                    }

                    if (cardElement.Height == AdaptiveHeight.Auto)
                    {
                        uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                        Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                        uiContainer.Children.Add(uiElement);
                    }
                    else
                    {
                        if (cardElement.Type == "Container")
                        {
                            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
                            Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                            uiContainer.Children.Add(uiElement);
                        }
                        else
                        {
                            StackPanel panel = new StackPanel();
                            panel.Children.Add(uiElement);

                            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
                            Grid.SetRow(panel, uiContainer.RowDefinitions.Count - 1);
                            uiContainer.Children.Add(panel);
                        }
                    }

                    renderedElements.Add(new Tuple<AdaptiveElement, FrameworkElement>(cardElement, uiElement));
                }
            }

            // Apply margins from parent
            // We do this after rendering to make sure we apply to the first and last RENDERED child... since a child could fail to render, changing which one is "last"
            foreach (var renderedElement in renderedElements)
            {
                var marginFromParent = parentDesiredMarginFromParent.CombineWith(renderedElement.Item1.MarginFromParent);

                renderedElement.Item2.Margin = new Thickness(
                    left: context.Config.GetSpacing(marginFromParent.Left.Value),
                    top: renderedElement == renderedElements.First() ? context.Config.GetSpacing(marginFromParent.Top.Value) : renderedElement.Item2.Margin.Top,
                    right: context.Config.GetSpacing(marginFromParent.Right.Value),
                    bottom: renderedElement == renderedElements.Last() ? context.Config.GetSpacing(marginFromParent.Bottom.Value) : renderedElement.Item2.Margin.Bottom);
            }
        }

        public static void AddSeperator(AdaptiveRenderContext context, AdaptiveElement element, Grid uiContainer)
        {
            if (element.Spacing == AdaptiveSpacing.None && !element.Separator)
                return;

            var uiSep = new Grid();
            uiSep.Style = context.GetStyle($"Adaptive.Separator");
            int spacing = context.Config.GetSpacing(element.Spacing);

            SeparatorConfig sepStyle = context.Config.Separator;

            uiSep.Margin = new Thickness(0, (spacing - sepStyle.LineThickness) / 2, 0, 0);
            uiSep.SetHeight(sepStyle.LineThickness);
            if(!string.IsNullOrWhiteSpace(sepStyle.LineColor))
                uiSep.SetBackgroundColor(sepStyle.LineColor,context);
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiSep);
        }
    }
}
