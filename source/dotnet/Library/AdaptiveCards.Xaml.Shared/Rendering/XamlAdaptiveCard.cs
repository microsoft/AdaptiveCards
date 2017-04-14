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
    public class XamlAdaptiveCard : AdaptiveCard, IRender<FrameworkElement, RenderContext>
    {
        public FrameworkElement Render(RenderContext context)
        {
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");
#if WPF
            outerGrid.Background = context.GetColorBrush(context.Options.AdaptiveCard.BackgroundColor);
            if (this.BackgroundImage != null)
            {
                outerGrid.Background = new ImageBrush(context.ResolveImageSource(this.BackgroundImage));
            }
#elif XAMARIN
            // TODO outerGrid.Background = context.GetColorBrush(context.Styling.BackgroundColor);
            if (this.BackgroundImage != null)
            {
                outerGrid.SetBackgroundImage(new Uri(this.BackgroundImage));
            }
#endif

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.Margin = new Thickness(context.Options.AdaptiveCard.Padding.Left,
                context.Options.AdaptiveCard.Padding.Top,
                context.Options.AdaptiveCard.Padding.Right,
                context.Options.AdaptiveCard.Padding.Bottom);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            XamlContainer.AddContainerElements(grid, this.Body, context);
            XamlActionSet.AddActions(grid, this.Actions, context, context.Options.AdaptiveCard.SupportedActionTypes, context.Options.AdaptiveCard.MaxActions);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }
    }
}

