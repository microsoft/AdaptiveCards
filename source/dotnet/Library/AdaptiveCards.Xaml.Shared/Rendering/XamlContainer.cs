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
using AsNum.XFControls;
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlContainer
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            Container container = (Container)element;
            var uiContainer = new Grid();
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

            return uiContainer;
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
                        if (cardElement.Separation != SeparationStyle.None)
                        {

                            var uiSep = new Grid();
                            uiSep.Style = context.GetStyle($"Adaptive.Separator");
                            SeparationOption sepStyle = null;
                            switch (cardElement.Separation)
                            {
                                case SeparationStyle.Default:
                                    sepStyle = context.Options.GetElementStyling(cardElement).Separation.Default;
                                    break;

                                case SeparationStyle.Strong:
                                    sepStyle = context.Options.GetElementStyling(cardElement).Separation.Strong;
                                    break;
                            }

                            uiSep.Margin = new Thickness(0, (sepStyle.Spacing - sepStyle.LineThickness) / 2, 0, (sepStyle.Spacing - sepStyle.LineThickness) / 2);
#if WPF
                            uiSep.Height = sepStyle.LineThickness;
                            if (sepStyle.LineColor != null)
                                uiSep.Background = context.GetColorBrush(sepStyle.LineColor);
#elif XAMARIN
                            // TODO
#endif
                            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                            Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
                            uiContainer.Children.Add(uiSep);
                        }
                    }
                    uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(uiElement);
                }
            }
        }
    }
}