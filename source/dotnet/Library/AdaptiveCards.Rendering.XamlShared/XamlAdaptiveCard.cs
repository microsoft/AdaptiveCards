using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

#if WPF

// using Adaptive.Threading.Tasks.Schedulers;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XamlAdaptiveCard
    {
        public static FrameworkElement Render(AdaptiveCard card, RenderContext context)
        {
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");
#if WPF
            //TODO for Xamarin
            outerGrid.Background = context.GetColorBrush(context.Config.ContainerStyles.Default.BackgroundColor);
#endif

            outerGrid.SetBackgroundSource(card.BackgroundImage,context);

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.Margin = new Thickness(context.Config.Spacing.Padding,
                context.Config.Spacing.Padding,
                context.Config.Spacing.Padding,
                context.Config.Spacing.Padding);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            XamlContainer.AddContainerElements(grid, card.Body, context);
            XamlActionSet.AddActions(grid, card.Actions, context);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }
    }
}

