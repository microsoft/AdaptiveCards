using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveContainerRenderer
    {
        public static FrameworkElement Render(AdaptiveContainer container, AdaptiveRenderContext context)
        {
            var containerStyle = context.Config.ContainerStyles.Default;
            var uiContainer = new Grid();
            //uiContainer.Margin = new Thickness(context.Config.Spacing.Padding);
            uiContainer.Style = context.GetStyle("Adaptive.Container");
            AddContainerElements(uiContainer, container.Items, context);

            if (container.SelectAction != null)
            {
                return context.RenderSelectAction(container.SelectAction, uiContainer);
            }

            Grid uiOuterContainer = new Grid();
            uiOuterContainer.Background = context.GetColorBrush(containerStyle.BackgroundColor);
            uiOuterContainer.Children.Add(uiContainer);
            Border border = new Border();
            border.Child = uiOuterContainer;
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
                        AddSeperator(context, cardElement, uiContainer);
                    }
                    else if (uiContainer.Children.Count > 0)
                    {
                        var spacing = context.Config.GetSpacing(cardElement.Spacing);                        
                        uiElement.Margin = new Thickness(0, spacing, 0, 0);
                    }

                    // do some sizing magic using the magic GridUnitType.Star
                    var height = cardElement.Height?.ToLower();
                    if (height == AdaptiveElementHeight.Stretch.ToLower())
                        uiContainer.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
                    else if (height == AdaptiveElementHeight.Auto.ToLower())
                        uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    else if (height == null)
                        uiContainer.RowDefinitions.Add(new RowDefinition() { SharedSizeGroup = "Row" + uiContainer.RowDefinitions.Count });
                    else
                    {
                        double val;
                        if (double.TryParse(height, out val))
                            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(val, GridUnitType.Star) });
                        else
                            uiContainer.RowDefinitions.Add(new RowDefinition() { SharedSizeGroup = "Row" + uiContainer.RowDefinitions.Count });
                    }

                    Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(uiElement);
                }
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