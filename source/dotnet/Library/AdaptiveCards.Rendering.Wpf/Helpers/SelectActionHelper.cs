using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveRenderContextExtensions
    {
        public static FrameworkElement RenderSelectAction(this AdaptiveRenderContext context, AdaptiveAction selectAction, FrameworkElement uiElement)
        {
            if (context.Config.SupportsInteractivity)
            {
                var uiButton = (Button)context.Render(selectAction);
                uiButton.HorizontalAlignment = HorizontalAlignment.Left;
                uiButton.Background = new SolidColorBrush(Colors.Transparent);
                uiButton.BorderThickness = new Thickness(0);
                uiButton.Content = uiElement;
                uiButton.Style = context.GetStyle("Adaptive.Action.Tap");

                // Handle ShowCard
                if (selectAction is AdaptiveShowCardAction showCardAction)
                {
                    var actionsConfig = context.Config.Actions;
                    bool isInline = (actionsConfig.ShowCard.ActionMode == ShowCardActionMode.Inline);
                    if (isInline && context.CardDepth == 1)
                    {
                        FrameworkElement uiShowCardContainer = showCardAction.CreateShowCard(context, actionsConfig);
                        context.ActionShowCards.Add(new Tuple<FrameworkElement, Button>(uiShowCardContainer, uiButton));
                    }
                }

                return uiButton;
            }

            return uiElement;
        }

        public static FrameworkElement CreateShowCard(this AdaptiveShowCardAction showCardAction, AdaptiveRenderContext context, ActionsConfig actionsConfig)
        {
            Grid uiShowCardContainer = new Grid();
            uiShowCardContainer.Style = context.GetStyle("Adaptive.Actions.ShowCard");
            uiShowCardContainer.DataContext = showCardAction;
            uiShowCardContainer.Margin = new Thickness(0, actionsConfig.ShowCard.InlineTopMargin, 0, 0);
            uiShowCardContainer.Visibility = Visibility.Collapsed;

            // render the card
            var uiShowCardWrapper = (Grid)context.Render(showCardAction.Card);
            uiShowCardWrapper.Background = context.GetColorBrush("Transparent");
            uiShowCardWrapper.DataContext = showCardAction;

            // Remove the card padding
            var innerCard = (Grid)uiShowCardWrapper.Children[0];
            innerCard.Margin = new Thickness(0);

            uiShowCardContainer.Children.Add(uiShowCardWrapper);

            return uiShowCardContainer;
        }
    }
}