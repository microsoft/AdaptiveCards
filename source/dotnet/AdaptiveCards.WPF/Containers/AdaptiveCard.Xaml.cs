using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.IO;
using System.Net;
using System.Threading;
using System.Windows;
#if WPF
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
// using Adaptive.Threading.Tasks.Schedulers;
#elif Xamarin
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {

        protected override FrameworkElement Render(AdaptiveCard card, RenderContext context)
        {
            var outerGrid = new Grid();
            outerGrid.Style = this.GetStyle("Adaptive.Card");
            if (card.BackgroundImage != null)
            {
#if WPF
                if (card.BackgroundImage != null)
                {
                    outerGrid.Background = new ImageBrush(context.ResolveImageSource(card.BackgroundImage));
                }
#elif Xamarin
                if (card.BackgroundImage != null)
                {
                    outerGrid.SetBackgroundImage(new Uri(card.BackgroundImage));
                }
#endif
            }

            var grid = new Grid();
            grid.Style = this.GetStyle("Adaptive.InnerCard");
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            AddContainerElements(grid, card.Body, card.Actions, context);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }
    }
}

