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
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{
    public static class XamlAdaptiveCard
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            AdaptiveCard card = (AdaptiveCard)element;
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");
#if WPF
            //TODO for Xamarin
            outerGrid.Background = context.GetColorBrush(context.Config.AdaptiveCard.BackgroundColor);
#endif

            outerGrid.SetBackgroundSource(card.BackgroundImage,context);

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.Margin = new Thickness(context.Config.AdaptiveCard.Padding.Left,
                context.Config.AdaptiveCard.Padding.Top,
                context.Config.AdaptiveCard.Padding.Right,
                context.Config.AdaptiveCard.Padding.Bottom);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            XamlContainer.AddContainerElements(grid, card.Body, context);
            XamlActionSet.AddActions(grid, card.Actions, context);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }
    }
}

