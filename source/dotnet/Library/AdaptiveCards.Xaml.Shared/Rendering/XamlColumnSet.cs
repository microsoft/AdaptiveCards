using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
#if WPF
using System.Windows.Controls;
using System.Windows.Shapes;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlColumnSet 
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            ColumnSet columnSet = (ColumnSet)element;
            var uiColumnSet = new Grid();
            uiColumnSet.Style = context.GetStyle($"Adaptive.{columnSet.Type}");

            foreach (var column in columnSet.Columns)
            {
                FrameworkElement uiContainer = context.Render(column);

                // Add vertical Seperator
                if (uiColumnSet.ColumnDefinitions.Count > 0)
                {
                    if (column.Separation != SeparationStyle.None)
                    {

                        var uiSep = new Grid();
                        uiSep.Style = context.GetStyle($"Adaptive.VerticalSeparator");
#if WPF
                    uiSep.VerticalAlignment = VerticalAlignment.Stretch;
#elif XAMARIN
                        // TOOD: check xamarin separator visual
                        //sep.VerticalAlignment = VerticalAlignment.Stretch;
#endif
                        SeparationConfig sepStyle;
                        switch (column.Separation)
                        {
                            case SeparationStyle.Strong:
                                sepStyle = context.Config.GetSeparationForElement(element, true);
                                break;

                            case SeparationStyle.Default:
                            default:
                                sepStyle = context.Config.GetSeparationForElement(element, false);
                                break;
                        }
                        uiSep.Margin = new Thickness(sepStyle.Spacing / 2, 0, sepStyle.Spacing / 2, 0);
#if WPF
                    uiSep.Width = sepStyle.LineThickness;
                    if (sepStyle.LineColor != null)
                        uiSep.Background = context.GetColorBrush(sepStyle.LineColor);
#elif XAMARIN
                        // TODO
#endif
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                        Grid.SetColumn(uiSep, uiColumnSet.ColumnDefinitions.Count - 1);
                        uiColumnSet.Children.Add(uiSep);
                    }

                }


                // do some sizing magic using the magic GridUnitType.Star
                var size = column.Size?.ToLower();
                if (size == null || size == ColumnSize.Stretch.ToLower())
                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                else if (size == ColumnSize.Auto.ToLower())
                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                else
                {
                    double val;
                    if (double.TryParse(size, out val))
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(val, GridUnitType.Star) });
                    else
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                }

                Grid.SetColumn(uiContainer, uiColumnSet.ColumnDefinitions.Count - 1);
                uiColumnSet.Children.Add(uiContainer);
            }

            if (columnSet.SelectAction != null)
            {
                var uiButton = (Button)context.Render(columnSet.SelectAction);
                if (uiButton != null)
                {
                    uiButton.Content = uiColumnSet;
                    uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }
            return uiColumnSet;
        }

    }
}