// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveActionSetRenderer
    {
        public static FrameworkElement Render(AdaptiveActionSet actionSet, AdaptiveRenderContext context)
        {
            var outerActionSet = new Grid();

            if (!context.Config.SupportsInteractivity)
                return outerActionSet;

            outerActionSet.Style = context.GetStyle("Adaptive.Container");

            // Keep track of ContainerStyle.ForegroundColors before Container is rendered
            var parentRenderArgs = context.RenderArgs;
            var elementRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            AddActions(outerActionSet, actionSet.Actions, context);

            return outerActionSet;
        }

        public static void AddActions(Grid uiContainer, IList<AdaptiveAction> actions, AdaptiveRenderContext context)
        {
            if (!context.Config.SupportsInteractivity)
                return;

            var actionsConfig = context.Config.Actions;
            var maxActions = actionsConfig.MaxActions;
            var actionsToProcess = GetActionsToProcess(actions, maxActions);

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

                // See if all actions have icons, otherwise force the icon placement to the left
                var oldConfigIconPlacement = actionsConfig.IconPlacement;
                bool allActionsHaveIcons = true;
                foreach (var action in actionsToProcess)
                {
                    if (string.IsNullOrEmpty(action.IconUrl))
                    {
                        allActionsHaveIcons = false;
                        break;
                    }
                }

                if (!allActionsHaveIcons)
                {
                    actionsConfig.IconPlacement = IconPlacement.LeftOfTitle;
                }

                int showCardActionCount = 0;

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
                        // If there are no showCards yet, create the dictionary for hosting the <button, card> mapping
                        if (!context.ActionShowCardsInContainer.ContainsKey(uiContainer))
                        {
                            context.ActionShowCardsInContainer.Add(uiContainer, new List<Button>());
                        }

                        showCardActionCount++;

                        // Only support 1 level of showCard
                        if (isInline && context.CardDepth == 1)
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

                            // Add to the list of show cards in context
                            context.ActionShowCards[uiAction] = uiShowCardContainer;

                            // Tie rendered button to container of showCards 
                            context.ShowCardContainerForButton[uiAction] = uiContainer;

                            // Tie rendered card to its container
                            context.ActionShowCardsInContainer[uiContainer].Add(uiAction);
                        }
                    }
                }

                // If there are any showCard actions, then create a row to host the hidden cards
                if (showCardActionCount > 0)
                {
                    uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                }

                foreach (var showCardAction in context.ActionShowCardsInContainer[uiContainer])
                {
                    var uiButton = showCardAction;
                    var currentShowCard = context.ActionShowCards[uiButton];

                    Grid.SetRow(currentShowCard, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(currentShowCard);

                    // Assign on click function to all button elements
                    uiButton.Click += (sender, e) =>
                    {
                        bool isCardCollapsed = (currentShowCard.Visibility != Visibility.Visible);

                        // Collapse all the show cards
                        foreach (var actionShowCard in context.ActionShowCardsInContainer[uiContainer])
                        {
                            var showCard = context.ActionShowCards[actionShowCard];
                            showCard.Visibility = Visibility.Collapsed;
                        }

                        // If current card is previously collapsed, show it
                        if (isCardCollapsed)
                        {
                            currentShowCard.Visibility = Visibility.Visible;
                        }
                    };
                }

                // Restore the iconPlacement for the context.
                actionsConfig.IconPlacement = oldConfigIconPlacement;
            }
        }

        private static List<AdaptiveAction> GetActionsToProcess(IList<AdaptiveAction> actions, int maxActions)
        {
            // only consider known actions for ActionsToProcess
            var actionsToProcess = actions.Where(obj => obj.GetType() != typeof(AdaptiveUnknownAction)).ToList();
            return actionsToProcess.Take(maxActions).ToList();
        }
    }
}
