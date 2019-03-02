using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

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
            var outerStyle = context.ForegroundColors;
            var parentContainerStyle = context.ParentStyle;

            if (container.Style != null)
            {
                ApplyPadding(uiContainer, container, parentContainerStyle, context);

                // Apply background color
                ContainerStyleConfig containerStyle = context.Config.ContainerStyles.GetContainerStyleConfig(container.Style);
                uiContainer.SetBackgroundColor(containerStyle.BackgroundColor, context);

                context.ForegroundColors = containerStyle.ForegroundColors;
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

            // Modify context outer parent style so padding necessity can be determined
            AdaptiveContainerStyle containerContainerStyle = container.Style ?? parentContainerStyle;
            if (containerContainerStyle == AdaptiveContainerStyle.None)
            {
                containerContainerStyle = parentContainerStyle;
            }
            context.ParentStyle = containerContainerStyle;

            AddContainerElements(uiContainer, container.Items, context);

            if (container.SelectAction != null)
            {
                return context.RenderSelectAction(container.SelectAction, uiContainer);
            }

            Grid uiOuterContainer = new Grid();
            uiOuterContainer.Children.Add(uiContainer);
            Border border = new Border();
            border.Child = uiOuterContainer;

            if(!container.IsVisible)
            {
                border.Visibility = Visibility.Collapsed;
            }

            // Revert context's value to that of outside the Container
            context.ForegroundColors = outerStyle;
            context.ParentStyle = parentContainerStyle;
            return border;
        }

        public static void AddContainerElements(Grid uiContainer, IList<AdaptiveElement> elements, AdaptiveRenderContext context)
        {
            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = context.Render(cardElement);
                if (uiElement != null)
                {
                    if (cardElement.Separator && uiContainer.Children.Count > 0)
                    {
                        AddSeparator(context, cardElement, uiContainer);
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

                }
            }
        }

        public static void AddSeparator(AdaptiveRenderContext context, AdaptiveElement element, Grid uiContainer)
        {
            if (element.Spacing == AdaptiveSpacing.None && !element.Separator)
                return;

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
        }

        public static void ApplyPadding(Grid uiElement, AdaptiveTypedElement element, AdaptiveContainerStyle parentStyle, AdaptiveRenderContext context)
        {
            bool canApplyPadding = false;

            // AdaptiveColumn inherits from AdaptiveContainer so only one check is required for both
            if (element is AdaptiveContainer container)
            {
                canApplyPadding = ((container.BackgroundImage != null) || ((container.Style != AdaptiveContainerStyle.None) && (container.Style != parentStyle)));
            }
            else if (element is AdaptiveColumnSet columnSet)
            {
                canApplyPadding = ((columnSet.Style != AdaptiveContainerStyle.None) && (columnSet.Style != parentStyle));
            }

            if (canApplyPadding)
            {
                int padding = context.Config.Spacing.Padding;
                Thickness paddingThickness = new Thickness { Left = padding, Right = padding };
                uiElement.Margin = paddingThickness;
            }
        }
    }
}
