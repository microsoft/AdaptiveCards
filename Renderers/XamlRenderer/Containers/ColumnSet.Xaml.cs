using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Adaptive
{
    public partial class ColumnSet
    {

        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<ColumnSet, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// ColumnSet
        /// </summary>
        /// <param name="columnSet"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            var uiColumnSet = new Grid();
            uiColumnSet.Style = context.GetStyle("Adaptive.ColumnSet");

            foreach (var column in this.Columns)
            {
                // Add vertical Seperator
                if (uiColumnSet.ColumnDefinitions.Count > 0)
                {
                    switch (column.Separation)
                    {
                        case SeparationStyle.None:
                            break;
                        case SeparationStyle.Default:
                            {
                                var sep = new Rectangle();
                                sep.Style = context.GetStyle($"Adaptive.VerticalSeparator");
                                uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                                Grid.SetColumn(sep, uiColumnSet.ColumnDefinitions.Count - 1);
                                uiColumnSet.Children.Add(sep);
                            }
                            break;

                        case SeparationStyle.Strong:
                            {
                                var sep = new Rectangle();
                                sep.VerticalAlignment = VerticalAlignment.Stretch;
                                sep.Style = context.GetStyle($"Adaptive.VerticalSeparator.Strong");
                                uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                                Grid.SetColumn(sep, uiColumnSet.ColumnDefinitions.Count - 1);
                                uiColumnSet.Children.Add(sep);
                            }
                            break;
                    }
                }

                FrameworkElement uiElement = column.Render(context);

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

                Grid.SetColumn(uiElement, uiColumnSet.ColumnDefinitions.Count - 1);
                uiColumnSet.Children.Add(uiElement);
            }

            return uiColumnSet;
        }
    }
}