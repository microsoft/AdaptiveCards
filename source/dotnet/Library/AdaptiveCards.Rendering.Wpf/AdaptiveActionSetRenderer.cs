using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveActionSetRenderer
    {
        public static void AddActions(Grid uiContainer, IList<AdaptiveAction> actions, AdaptiveRenderContext context)
        {
            if (!context.Config.SupportsInteractivity)
                return;

            var actionsConfig = context.Config.Actions;
            var maxActions = actionsConfig.MaxActions;
            var actionsToProcess = actions
                .Take(maxActions).ToList();

            if (actionsToProcess.Any())
            {
                var uiActionBar = new UniformGrid();

                if (actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal)
                    uiActionBar.Columns = actionsToProcess.Count();
                else
                    uiActionBar.Rows = actionsToProcess.Count();

                uiActionBar.HorizontalAlignment = (HorizontalAlignment)Enum.Parse(typeof(HorizontalAlignment), actionsConfig.ActionAlignment.ToString());
                uiActionBar.VerticalAlignment = VerticalAlignment.Bottom;
                uiActionBar.Style = context.GetStyle("Adaptive.Actions");

                // For vertical, we want to subtract the top margin of the first button
                var topMargin = actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal
                    ? context.Config.GetSpacing(actionsConfig.Spacing)
                    : context.Config.GetSpacing(actionsConfig.Spacing) - actionsConfig.ButtonSpacing;

                uiActionBar.Margin = new Thickness(0, topMargin, 0, 0);

                uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, uiContainer.RowDefinitions.Count - 1);
                uiContainer.Children.Add(uiActionBar);

                bool isInline = (actionsConfig.ShowCard.ActionMode == ShowCardActionMode.Inline);

                int iPos = 0;
                foreach (var action in actionsToProcess)
                {
                    // add actions
                    var uiAction = (Button)context.Render(action);


                    if (actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal)
                    {
                        if (uiActionBar.Children.Count > 0) // don't apply left margin to the first item
                            uiAction.Margin = new Thickness(actionsConfig.ButtonSpacing, 0, 0, 0);
                    }
                    else
                    {
                        uiAction.Margin = new Thickness(0, actionsConfig.ButtonSpacing, 0, 0);
                    }


                    if (actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal)
                        Grid.SetColumn(uiAction, iPos++);

                    uiActionBar.Children.Add(uiAction);

                    if (action is AdaptiveShowCardAction showCardAction)
                    {
                        if (isInline && context.CardDepth == 1)
                        {
                            FrameworkElement uiShowCardContainer = CreateShowCard(showCardAction, context, actionsConfig);
                            context.ActionShowCards.Add(new Tuple<FrameworkElement, Button>(uiShowCardContainer, uiAction));
                        }
                    }
                }
            }
        }

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
                        FrameworkElement uiShowCardContainer = CreateShowCard(showCardAction, context, actionsConfig);
                        context.ActionShowCards.Add(new Tuple<FrameworkElement, Button>(uiShowCardContainer, uiButton));
                    }
                }

                return uiButton;
            }

            return uiElement;
        }

        private static FrameworkElement CreateShowCard(AdaptiveShowCardAction showCardAction, AdaptiveRenderContext context, ActionsConfig actionsConfig)
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