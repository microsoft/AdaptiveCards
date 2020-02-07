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
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveCard card = (AdaptiveCard)element;

            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");

#if WPF
            //TODO for Xamarin
            outerGrid.Background = context.GetColorBrush(context.Config.AdaptiveCard.BackgroundColor);
#elif XAMARIN
            // outerGrid.BackgroundColor = context.GetColorBrush(context.Config.ContainerStyles.Default.BackgroundColor);
#endif
            // outerGrid.SetBackgroundSource(card.BackgroundImage, context);

            if (context.CardRoot == null)
            {
                context.CardRoot = outerGrid;
            }

            // Reset the parent style
            // context.RenderArgs.ParentStyle = AdaptiveContainerStyle.Default;

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.Margin = new Thickness(context.Config.Spacing.Padding);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            switch (card.VerticalContentAlignment)
            {
                case AdaptiveVerticalContentAlignment.Center:
#if WPF
                    grid.VerticalAlignment = VerticalAlignment.Center;
#elif XAMARIN
                    grid.VerticalOptions = LayoutOptions.FillAndExpand;
#endif
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
#if WPF
                    grid.VerticalAlignment = VerticalAlignment.Bottom;
#elif XAMARIN
                    grid.VerticalOptions = LayoutOptions.End;
#endif
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    break;
            }

#if WPF
            outerGrid.MinHeight = card.PixelMinHeight;     
#elif XAMARIN
            outerGrid.MinimumHeightRequest = card.PixelMinHeight;
#endif

            outerGrid.Children.Add(grid);

            var inputControls = new List<FrameworkElement>();
                     
            AdaptiveContainerRenderer.AddContainerElements(grid, card.Body, context);
            AdaptiveActionSetRenderer.AddActions(grid, card.Actions, context, card.InternalID);


            if (card.SelectAction != null)
            {
                // var outerGridWithSelectAction = context.RenderSelectAction(card.SelectAction, outerGrid);

                // return outerGridWithSelectAction;
            }

            return outerGrid;
        }
    }
}

