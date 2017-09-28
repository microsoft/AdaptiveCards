using System.Collections.Generic;
using System.Linq;
using System.Windows;
using AdaptiveCards.Rendering;
using System;
using AdaptiveCards.Rendering.Config;
#if WPF
using System.Windows.Shapes;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlContainer
    {
        public static FrameworkElement Render(Container container, RenderContext context)
        {
            var containerStyle = context.Config.Container.Normal;
            var uiContainer = new Grid();
            uiContainer.Margin = new Thickness(containerStyle.Padding.Left, containerStyle.Padding.Top, containerStyle.Padding.Right, containerStyle.Padding.Bottom);
            uiContainer.Style = context.GetStyle("Adaptive.Container");
            AddContainerElements(uiContainer, container.Items, context);

            if (container.SelectAction != null)
            {
                var uiButton = (Button)context.Render(container.SelectAction);//, new RenderContext(container.actionCallback, container.missingDataCallback));
                if (uiButton != null)
                {
                    uiButton.Content = uiContainer;
                    uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }

#if WPF 
            Grid uiOuterContainer = new Grid();
            uiOuterContainer.Background = context.GetColorBrush(containerStyle.BackgroundColor);
            uiOuterContainer.Children.Add(uiContainer);
            Border border = new Border()
            {
                BorderBrush = context.GetColorBrush(containerStyle.BorderColor),
                BorderThickness = new Thickness(containerStyle.BorderThickness.Left, containerStyle.BorderThickness.Top, containerStyle.BorderThickness.Right, containerStyle.BorderThickness.Bottom)
            };
            border.Child = uiOuterContainer;
            return border;
#else
            // TODO for xamarin
            return uiContainer;
#endif 
        }

        public static void AddContainerElements(Grid uiContainer, List<CardElement> elements, RenderContext context)
        {
            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = context.Render(cardElement);
                if (uiElement != null)
                {
                    if (uiContainer.RowDefinitions.Count > 0)
                    {
                        AddSeperator(context, cardElement, uiContainer, cardElement.Separation);
                    }
                    uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(uiElement);
                }
            }
        }

        public static void AddSeperator(RenderContext context, CardElement element, Grid uiContainer, SeparationStyle seperationStyle)
        {
            if (seperationStyle == SeparationStyle.None)
                return;

            var uiSep = new Grid();
            uiSep.Style = context.GetStyle($"Adaptive.Separator");
            SeparationConfig sepStyle = null;
            switch (seperationStyle)
            {
                case SeparationStyle.Default:
                    sepStyle = context.Config.GetSeparationForElement(element, strong: false);
                    break;

                case SeparationStyle.Strong:
                    sepStyle = context.Config.GetSeparationForElement(element, strong: true);
                    break;
            }
            
            uiSep.Margin = new Thickness(0, (sepStyle.Spacing - sepStyle.LineThickness) / 2, 0, (sepStyle.Spacing - sepStyle.LineThickness) / 2);
            uiSep.SetHeight(sepStyle.LineThickness);
            if(!string.IsNullOrWhiteSpace(sepStyle.LineColor))
                uiSep.SetBackgroundColor(sepStyle.LineColor,context);
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiSep);            
        }
    }
}