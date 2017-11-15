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
        public static void AddActions(Grid uiContainer, IList<AdaptiveAction> actions, AdaptiveRenderContext context)
        {
            var maxActions = context.Config.Actions.MaxActions;
            var actionsToProcess = actions
                .Take(maxActions).ToList();

            if (actionsToProcess.Any())
            {
                var uiActionBar = new UniformGrid();

                if (context.Config.Actions.ActionsOrientation == ActionsOrientation.Horizontal)
                    uiActionBar.Columns = actionsToProcess.Count();
                else
                    uiActionBar.Rows = actionsToProcess.Count();

                uiActionBar.HorizontalAlignment = (HorizontalAlignment)Enum.Parse(typeof(HorizontalAlignment), context.Config.Actions.ActionAlignment.ToString());
                uiActionBar.VerticalAlignment = VerticalAlignment.Bottom;
                uiActionBar.Style = context.GetStyle("Adaptive.Actions");
                uiActionBar.Margin = new Thickness(0, context.Config.GetSpacing(AdaptiveSpacing.Default), 0, 0);

                uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, uiContainer.RowDefinitions.Count - 1);
                uiContainer.Children.Add(uiActionBar);

                bool isInline = (context.Config.Actions.ShowCard.ActionMode == ShowCardActionMode.Inline);

                if (isInline && actionsToProcess.Any(a => a is AdaptiveShowCardAction))
                {
                    uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                }

                int iPos = 0;
                List<FrameworkElement> actionBarCards = new List<FrameworkElement>();
                foreach (var action in actionsToProcess)
                {
                    // add actions
                    var uiAction = (Button)context.Render(action);
                    if (uiAction != null)
                    {
                        if (uiActionBar.Children.Count > 0)
                        {
                            if (context.Config.Actions.ActionsOrientation == ActionsOrientation.Horizontal)
                                uiAction.Margin = new Thickness(context.Config.Actions.ButtonSpacing, 0, 0, 0);
                            else
                                uiAction.Margin = new Thickness(0, context.Config.Actions.ButtonSpacing, 0, 0);
                        }

                        if (context.Config.Actions.ActionsOrientation == ActionsOrientation.Horizontal)
                            Grid.SetColumn(uiAction, iPos++);

                        uiActionBar.Children.Add(uiAction);

                        if (action is AdaptiveShowCardAction)
                        {
                            AdaptiveShowCardAction adaptiveShowCardAction = (AdaptiveShowCardAction)action;
                            if (isInline)
                            {
                                Grid uiShowCardContainer = new Grid();
                                uiShowCardContainer.Style = context.GetStyle("Adaptive.Actions.ShowCard");
                                uiShowCardContainer.DataContext = adaptiveShowCardAction;
                                uiShowCardContainer.Margin = new Thickness(0, context.Config.Actions.ShowCard.InlineTopMargin, 0, 0);
                                uiShowCardContainer.Visibility = Visibility.Collapsed;

                                // render the card
                                var uiShowCard = context.Render(adaptiveShowCardAction.Card);
                                ((Grid)uiShowCard).Background = context.GetColorBrush("Transparent");
                                uiShowCard.DataContext = adaptiveShowCardAction;
                                uiShowCardContainer.Children.Add(uiShowCard);

                                actionBarCards.Add(uiShowCardContainer);
                                Grid.SetRow(uiShowCardContainer, uiContainer.RowDefinitions.Count - 1);
                                uiContainer.Children.Add(uiShowCardContainer);

                                uiAction.Click += (sender, e) =>
                                {
                                    bool showCard = (uiShowCardContainer.Visibility != Visibility.Visible);
                                    foreach (var actionBarCard in actionBarCards)
                                        actionBarCard.Visibility = Visibility.Collapsed;
                                    if (showCard)
                                        uiShowCardContainer.Visibility = Visibility.Visible;
                                };
                            }
                        }
                    }
                }
            }
        }
    }
}