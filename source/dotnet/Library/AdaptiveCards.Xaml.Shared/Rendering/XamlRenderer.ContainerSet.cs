using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
using System.Windows.Shapes;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
    {
        public static FrameworkElement RenderContainerSet(TypedElement element, RenderContext context)
        {
            ContainerSet containerSet = (ContainerSet)element;
            var uiContainerSet = new Grid();
            uiContainerSet.Style = context.GetStyle($"Adaptive.{element.Type}");

            foreach (var container in containerSet.Containers)
            {
                FrameworkElement uiContainer = context.Render(container);

                // Add vertical Seperator
                if (uiContainerSet.ColumnDefinitions.Count > 0)
                {
                    if (container.Separation != SeparationStyle.None)
                    {

                        var uiSep = new Grid();
                        uiSep.Style = context.GetStyle($"Adaptive.VerticalSeparator");
#if WPF
                    uiSep.VerticalAlignment = VerticalAlignment.Stretch;
#elif XAMARIN
                        // TOOD: check xamarin separator visual
                        //sep.VerticalAlignment = VerticalAlignment.Stretch;
#endif
                        SeparationOption sepStyle;
                        switch (container.Separation)
                        {
                            case SeparationStyle.Strong:
                                sepStyle = context.Options.Container.Separation.Strong;
                                break;

                            case SeparationStyle.Default:
                            default:
                                sepStyle = context.Options.Container.Separation.Default;
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
                        uiContainerSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                        Grid.SetColumn(uiSep, uiContainerSet.ColumnDefinitions.Count - 1);
                        uiContainerSet.Children.Add(uiSep);
                    }

                }


                // do some sizing magic using the magic GridUnitType.Star
                var size = container.Size?.ToLower();
                if (size == null || size == ColumnSize.Stretch.ToLower())
                    uiContainerSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                else if (size == ColumnSize.Auto.ToLower())
                    uiContainerSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                else
                {
                    double val;
                    if (double.TryParse(size, out val))
                        uiContainerSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(val, GridUnitType.Star) });
                    else
                        uiContainerSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                }

                Grid.SetColumn(uiContainer, uiContainerSet.ColumnDefinitions.Count - 1);
                uiContainerSet.Children.Add(uiContainer);
            }

            return uiContainerSet;
        }

    }
}