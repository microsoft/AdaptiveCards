// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
#if WPF
using System.Windows.Shapes;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using FrameworkElement = Xamarin.Forms.View;
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

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
            AdaptiveRenderArgs parentRenderArgs = context.RenderArgs;
            AdaptiveRenderArgs elementRenderArgs = new AdaptiveRenderArgs(parentRenderArgs);

            AddRenderedActions(outerActionSet, actionSet.Actions, context, actionSet.InternalID);

            return outerActionSet;
        }

        public static void AddRenderedActions(Grid uiContainer, IList<AdaptiveAction> actions, AdaptiveRenderContext context, AdaptiveInternalID actionSetId)
        {
            if (!context.Config.SupportsInteractivity)
                return;

            ActionsConfig actionsConfig = context.Config.Actions;
            int maxActions = actionsConfig.MaxActions;
            List<AdaptiveAction> actionsToProcess = GetActionsToProcess(actions, maxActions, context);

            if (actionsToProcess.Any())
            {
#if WPF
                var uiActionBar = new UniformGrid();

                if (actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal)
                    uiActionBar.Columns = actionsToProcess.Count();
                else
                    uiActionBar.Rows = actionsToProcess.Count();
#elif XAMARIN
                var uiActionBar = new Grid();
                if (actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal)
                {
                    for (int i = 0; i < actionsToProcess.Count(); i++)
                    {
                        uiActionBar.ColumnDefinitions.Add(new ColumnDefinition
                        {
                            Width = GridLength.Auto
                        });
                    }
                }
                else
                {
                    for (int i = 0; i < actionsToProcess.Count(); i++)
                    {
                        uiActionBar.RowDefinitions.Add(new RowDefinition
                        {
                            Height = GridLength.Auto
                        });
                    }
                }
#endif

#if WPF
                uiActionBar.HorizontalAlignment = (HorizontalAlignment)Enum.Parse(typeof(HorizontalAlignment), actionsConfig.ActionAlignment.ToString());
                uiActionBar.VerticalAlignment = VerticalAlignment.Bottom;
#endif
                uiActionBar.Style = context.GetStyle("Adaptive.Actions");

                // For vertical, we want to subtract the top margin of the first button
                int topMargin = actionsConfig.ActionsOrientation == ActionsOrientation.Horizontal
                    ? context.Config.GetSpacing(actionsConfig.Spacing)
                    : context.Config.GetSpacing(actionsConfig.Spacing) - actionsConfig.ButtonSpacing;

                uiActionBar.Margin = new Thickness(0, topMargin, 0, 0);

                uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, uiContainer.RowDefinitions.Count - 1);
                uiContainer.Children.Add(uiActionBar);

                bool isInline = (actionsConfig.ShowCard.ActionMode == ShowCardActionMode.Inline);

                int iPos = 0;

                // See if all actions have icons, otherwise force the icon placement to the left
                IconPlacement oldConfigIconPlacement = actionsConfig.IconPlacement;
                bool allActionsHaveIcons = true;
                foreach (AdaptiveAction action in actionsToProcess)
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

                // indicates showcard has not been seen if it's set false; meaningful only if it's used
                // when inline is supported
                bool hasSeenInlineShowCard = false;

                foreach (AdaptiveAction action in actionsToProcess)
                {
                    // add actions
                    var uiAction = context.Render(action) as Button;

                    if (uiAction == null)
                    {
                        context.Warnings.Add(new AdaptiveWarning(-1, $"action failed to render" +
                            $"and valid fallback wasn't present"));
                        continue;
                    }

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
                    {
                        Grid.SetColumn(uiAction, iPos++);
                    }
                    else
                    {
                        Grid.SetRow(uiAction, iPos++);
                    }

#if XAMARIN
                    if (actionsConfig.ActionAlignment == AdaptiveHorizontalAlignment.Center)
                    {
                        uiAction.HorizontalOptions = LayoutOptions.CenterAndExpand;
                    }
#endif

                    uiActionBar.Children.Add(uiAction);

                    if (action is AdaptiveShowCardAction showCardAction && isInline)
                    {
                        if (actionSetId != null)
                        {
                            // the button's context is used as key for retrieving the corresponding showcard
                            uiAction.SetContext(actionSetId);

                            if (!hasSeenInlineShowCard)
                            {
                                // Define a new row to contain all the show cards
                                uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                                // it's first showcard of the peers, create a new list
                                context.PeerShowCardsInActionSet[actionSetId] = new List<FrameworkElement>();
                            }

                            hasSeenInlineShowCard = true;

                            Grid uiShowCardContainer = new Grid();
                            uiShowCardContainer.Style = context.GetStyle("Adaptive.Actions.ShowCard");
#if WPF
                            uiShowCardContainer.DataContext = showCardAction;
                            uiShowCardContainer.Visibility = Visibility.Collapsed;
#elif XAMARIN
                            uiShowCardContainer.IsVisible = false;
#endif

                            var padding = context.Config.Spacing.Padding;
                            // set negative margin to expand the wrapper to the edge of outer most card
                            uiShowCardContainer.Margin = new Thickness(-padding, actionsConfig.ShowCard.InlineTopMargin, -padding, -padding);
                            var showCardStyleConfig = context.Config.ContainerStyles.GetContainerStyleConfig(actionsConfig.ShowCard.Style);
#if WPF
                            uiShowCardContainer.Background = context.GetColorBrush(showCardStyleConfig.BackgroundColor);
#endif

                            // render the card
                            var uiShowCardWrapper = (Grid)context.Render(showCardAction.Card);
#if WPF
                            uiShowCardWrapper.Background = context.GetColorBrush("Transparent");
                            uiShowCardWrapper.DataContext = showCardAction;
#endif

                            uiShowCardContainer.Children.Add(uiShowCardWrapper);
                            context.ActionShowCards.Add(uiAction, uiShowCardContainer);
                            // added the rendered show card as a peer
                            context.PeerShowCardsInActionSet[actionSetId].Add(uiShowCardContainer);
                            // define where in the rows of the parent Grid the show card will occupy
                            // and add it to the parent
                            Grid.SetRow(uiShowCardContainer, uiContainer.RowDefinitions.Count - 1);
                            uiContainer.Children.Add(uiShowCardContainer);
                        }
                        else
                        {
                            context.Warnings.Add(new AdaptiveWarning(-1, $"button's corresponding showCard" +
                                $" couldn't be added since the action set the button belongs to has null as internal id"));
                        }
                    }
                }

                // Restore the iconPlacement for the context.
                actionsConfig.IconPlacement = oldConfigIconPlacement;
            }
        }

        private static List<AdaptiveAction> GetActionsToProcess(IList<AdaptiveAction> actions, int maxActions, AdaptiveRenderContext context)
        {
            // If the number of actions is bigger than maxActions, then log warning for it
            if (actions.Count > maxActions)
            {
                context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.MaxActionsExceeded, "Some actions were not rendered due to exceeding the maximum number of actions allowed"));
            }

            // just take the first maxActions actions
            return actions.Take(maxActions).ToList();
        }
    }
}
