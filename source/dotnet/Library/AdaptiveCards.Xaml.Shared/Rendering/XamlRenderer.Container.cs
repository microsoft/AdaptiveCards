using System.Collections.Generic;
using System.Linq;
using System.Windows;
using AdaptiveCards.Rendering;
using System;
#if WPF
using System.Windows.Shapes;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using AsNum.XFControls;
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {

        /// <summary>
        /// Container
        /// </summary>
        /// <param name="container"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(Container container, RenderContext context)
        {
            var uiContainer = new Grid();
            uiContainer.Style = this.GetStyle("Adaptive.Container");

            AddContainerElements(uiContainer, container.Items, container.Actions, context, context.Options.Container.SupportedActions, context.Options.Container.MaxActions);

            if (container.SelectAction != null)
            {
                var uiButton = (Button)RenderAction(container.SelectAction, new RenderContext(this.actionCallback, this.missingDataCallback));
                if (uiButton != null)
                {
                    uiButton.Content = uiContainer;
                    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }

            return uiContainer;
        }

        protected void AddContainerElements(Grid uiContainer, List<CardElement> elements, List<ActionBase> actions, RenderContext context, string[] supportedActions, int maxActions)
        {
            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = this.Render(cardElement, context);
                if (uiElement != null)
                {
                    if (uiContainer.RowDefinitions.Count > 0)
                    {
                        var uiSep = new Grid();
                        uiSep.Style = this.GetStyle($"Adaptive.Separator");
                        SeparationOption sepStyle = null;
                        switch (cardElement.Separation)
                        {
                            case SeparationStyle.None:
                                sepStyle = context.Options.GetElementStyling(cardElement).Separation.None;
                                break;
                            case SeparationStyle.Default:
                                sepStyle = context.Options.GetElementStyling(cardElement).Separation.Default;
                                break;

                            case SeparationStyle.Strong:
                                sepStyle = context.Options.GetElementStyling(cardElement).Separation.Strong;
                                break;
                        }

                        uiSep.Margin = new Thickness(0, sepStyle.Spacing / 2, 0, sepStyle.Spacing / 2);
#if WPF
                        uiSep.Height = sepStyle.Thickness;
                        if (sepStyle.Color != null)
                            uiSep.Background = this.GetColorBrush(sepStyle.Color);
#elif XAMARIN
                            // TODO
#endif
                        uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                        Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
                        uiContainer.Children.Add(uiSep);
                    }
                    uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(uiElement);
                }
            }

            if (supportedActions != null)
            {
                var actionsToProcess = actions
                    .Where(a => supportedActions?.Contains(a.Type) == true)
                    .Take(maxActions).ToList();
                if (actionsToProcess.Any() == true)
                {
#if WPF
                    var uiActionBar = new UniformGrid();
                    if (context.Options.AdaptiveCard.ActionsOrientation == ActionsOrientation.Horizontal)
                        uiActionBar.Columns = actionsToProcess.Count();
                    else
                        uiActionBar.Rows = actionsToProcess.Count();
                    uiActionBar.HorizontalAlignment = (System.Windows.HorizontalAlignment)Enum.Parse(typeof(System.Windows.HorizontalAlignment), context.Options.AdaptiveCard.ActionAlignment.ToString());
                    uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

                    uiActionBar.Style = this.GetStyle("Adaptive.Actions");
                    uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    Grid.SetRow(uiActionBar, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(uiActionBar);

                    if (context.Options.Actions.ShowCard.ActionMode == ShowCardActionMode.Inline && actionsToProcess.Where(a => a is ActionShowCard).Any())
                    {
                        uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    }

                    int iPos = 0;
                    List<FrameworkElement> actionBarCards = new List<FrameworkElement>();
                    foreach (var action in actionsToProcess)
                    {
                        // add actions
                        var uiAction = (Button)this.RenderAction(action, context);
                        if (uiAction != null)
                        {
                            Grid.SetColumn(uiAction, iPos++);
                            uiActionBar.Children.Add(uiAction);

                            if (action is ActionShowCard)
                            {
                                ActionShowCard showCardAction = (ActionShowCard)action;
                                if (context.Options.Actions.ShowCard.ActionMode == ShowCardActionMode.Inline)
                                {
                                    Grid uiShowCardContainer = new Grid();
                                    uiShowCardContainer.Style = this.GetStyle("Adaptive.Actions.ShowCard");
                                    uiShowCardContainer.DataContext = showCardAction;
                                    if (context.Options.Actions.ShowCard.Margin.Length == 4)
                                        uiShowCardContainer.Margin = new Thickness(context.Options.Actions.ShowCard.Margin[0], context.Options.Actions.ShowCard.Margin[1], context.Options.Actions.ShowCard.Margin[2], context.Options.Actions.ShowCard.Margin[3]);
                                    else
                                        uiShowCardContainer.Margin = new Thickness(context.Options.Actions.ShowCard.Margin.First());
                                    uiShowCardContainer.Background = this.GetColorBrush(context.Options.Actions.ShowCard.BackgroundColor);
                                    uiShowCardContainer.Visibility = Visibility.Collapsed;

                                    // render the card
                                    var uiShowCard = Render(showCardAction.Card, context);
                                    if (context.Options.Actions.ShowCard.Padding.Length == 4)
                                        uiShowCard.Margin = new Thickness(context.Options.Actions.ShowCard.Padding[0], context.Options.Actions.ShowCard.Padding[1], context.Options.Actions.ShowCard.Padding[2], context.Options.Actions.ShowCard.Padding[3]);
                                    else
                                        uiShowCard.Margin = new Thickness(context.Options.Actions.ShowCard.Padding.First());
                                    uiShowCard.DataContext = showCardAction;
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

#elif XAMARIN
                var uiActionBar = new UniformGrid();
                //uiActionBar.Rows = 1;
                //uiActionBar.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                //uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

                int iCol = 0;
                foreach (var action in actionsToProcess)
                {
                    // add actions
                    var uiAction = this.RenderAction(action, context);
                    if (uiAction != null)
                    {
                        Grid.SetColumn(uiAction, iCol++);
                        uiActionBar.Children.Add(uiAction);
                    }
                }
                uiActionBar.Style = this.GetStyle("Adaptive.Actions");
                uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, uiContainer.RowDefinitions.Count - 1);
                uiContainer.Children.Add(uiActionBar);
#endif
                }
            }
        }

        private void Context_OnAction(object sender, ActionEventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}