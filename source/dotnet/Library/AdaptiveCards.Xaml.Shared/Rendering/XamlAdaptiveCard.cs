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
    public static class XamlAdaptiveCard
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            AdaptiveCard card = (AdaptiveCard)element;
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");
#if WPF
            outerGrid.Background = context.GetColorBrush(context.Options.AdaptiveCard.BackgroundColor);
            if (card.BackgroundImage != null)
            {
                outerGrid.Background = new ImageBrush(context.ResolveImageSource(card.BackgroundImage));
            }
#elif XAMARIN
            // TODO outerGrid.Background = context.GetColorBrush(context.Styling.BackgroundColor);
            if (card.BackgroundImage != null)
            {
                outerGrid.SetBackgroundImage(new Uri(card.BackgroundImage));
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
            XamlContainer.AddContainerElements(grid, card.Body, context);
            XamlActionSet.AddActions(grid, card.Actions, context, context.Options.SupportedActionTypes, context.Options.MaxActions);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }
    }
}

