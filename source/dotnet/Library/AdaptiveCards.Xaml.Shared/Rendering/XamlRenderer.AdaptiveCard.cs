using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.IO;
using System.Linq;
using System.Net;
using System.Threading;
using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
// using Adaptive.Threading.Tasks.Schedulers;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {

        protected override FrameworkElement Render(AdaptiveCard card, RenderContext context)
        {
            var outerGrid = new Grid();
            outerGrid.Style = this.GetStyle("Adaptive.Card");
#if WPF
            outerGrid.Background = this.GetColorBrush(context.Styling.BackgroundColor);
            if (card.BackgroundImage != null)
            {
                outerGrid.Background = new ImageBrush(context.ResolveImageSource(card.BackgroundImage));
            }
#elif XAMARIN
            // TODO outerGrid.Background = this.GetColorBrush(context.Styling.BackgroundColor);
            if (card.BackgroundImage != null)
            {
                outerGrid.SetBackgroundImage(new Uri(card.BackgroundImage));
            }
#endif

            var grid = new Grid();
            grid.Style = this.GetStyle("Adaptive.InnerCard");
            if (context.Styling.Margin.Length == 4)
                grid.Margin = new Thickness(context.Styling.Margin[0], context.Styling.Margin[1], context.Styling.Margin[2], context.Styling.Margin[3]);
            else
                grid.Margin = new Thickness(context.Styling.Margin.First());

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            AddContainerElements(grid, card.Body, card.Actions, context);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }
    }
}

