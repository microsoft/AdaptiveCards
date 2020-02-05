using System.Collections.Generic;
using System.Linq;
using System.Windows;
using AdaptiveCards.Rendering;
using System;
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
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            var containerStyle = context.Config.Spacing;
            AdaptiveContainer container = (AdaptiveContainer)element;
            var uiContainer = new Grid();
            uiContainer.Margin = new Thickness(containerStyle.Padding);
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

        public static void AddContainerElements(Grid uiContainer, List<AdaptiveElement> elements, RenderContext context)
        {
            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = context.Render(cardElement);
                if (uiElement != null)
                {
                    if (uiContainer.RowDefinitions.Count > 0)
                    {
                        AddSeparator(context, cardElement, uiContainer);
                    }
                    uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(uiElement);
                }
            }
        }

        public static void AddSeparator(RenderContext context, AdaptiveElement element, Grid uiContainer)
        {
            if (element.Spacing == AdaptiveSpacing.None && !element.Separator)
            {
                return;
            }

            var uiSep = new Grid();
            uiSep.Style = context.GetStyle($"Adaptive.Separator");
            int spacing = context.Config.GetSpacing(element.Spacing);

            SeparatorConfig sepStyle = context.Config.Separator;

            var margin = (spacing - sepStyle.LineThickness) / 2;
            uiSep.Margin = new Thickness(0, margin, 0, margin);
            uiSep.SetHeight(sepStyle.LineThickness);
            if (!string.IsNullOrWhiteSpace(sepStyle.LineColor))
            {
                uiSep.SetBackgroundColor(sepStyle.LineColor, context);
            }
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiSep);            
        }
    }
}
