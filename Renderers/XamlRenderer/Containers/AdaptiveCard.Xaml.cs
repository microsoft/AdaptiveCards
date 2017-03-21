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
    public partial class AdaptiveCard
    {
        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="card"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.Card");
            if (this.BackgroundImage != null)
            {
                Uri uri = new Uri(this.BackgroundImage);
                grid.Background = new ImageBrush(new BitmapImage(uri));
            }
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            Container.AddContainerElements(grid, this.Body, this.Actions, context);
            return grid;
        }
    }
}