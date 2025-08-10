// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
                // SelectAction doesn't allow showCard actions
                if (selectAction is AdaptiveShowCardAction)
                {
                    context.Warnings.Add(new AdaptiveWarning(-1, "Inline ShowCard not supported for SelectAction"));
                    return uiElement;
                }

                if (selectAction is AdaptiveSubmitAction || selectAction is AdaptiveExecuteAction)
                {
                    context.SubmitActionCardId[selectAction] = context.RenderArgs.ContainerCardId;
                }

                context.IsRenderingSelectAction = true;
                var uiButton = (Button) context.Render(selectAction);
                context.IsRenderingSelectAction = false;

                // Stretch both the button and button's content to avoid empty spaces
                uiButton.HorizontalAlignment = HorizontalAlignment.Stretch;
                uiButton.HorizontalContentAlignment = HorizontalAlignment.Stretch;

                // Adopt the child element's background to parent and set the child's background
                // to be transparent in order for button's on mouse hover color to work properly
                if (uiElement is Panel p)
                {
                    uiButton.Background = p.Background;
                    p.Background = new SolidColorBrush(Colors.Transparent);
                }
                else
                {
                    uiButton.Background = new SolidColorBrush(Colors.Transparent);
                }
                uiButton.BorderThickness = new Thickness(0);
                uiButton.Content = uiElement;
                uiButton.Style = context.GetStyle("Adaptive.Action.Tap");

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
