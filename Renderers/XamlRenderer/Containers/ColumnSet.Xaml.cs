using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Adaptive
{
    public partial class ColumnSet
    {

        /// <summary>
        /// ColumnSet
        /// </summary>
        /// <param name="columnSet"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            var uiColumnSet = new Grid();
            uiColumnSet.Style = context.GetStyle("Adaptive.ColumnSet");

            int iCol = 0;
            foreach (var column in this.Columns)
            {
                FrameworkElement uiElement = column.Render(context);

                // do some sizing magic using the magic GridUnitType.Star
                var size = column.Size?.ToLower();
                if (size == ColumnSize.Stretch.ToLower())
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

                Grid.SetColumn(uiElement, iCol++);
                uiColumnSet.Children.Add(uiElement);
            }

            return uiColumnSet;
        }
    }
}