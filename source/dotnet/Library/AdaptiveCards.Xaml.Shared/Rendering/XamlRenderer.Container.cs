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

            AddContainerElements(uiContainer, container.Items, container.Actions, context);

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

        protected void AddContainerElements(Grid grid, List<CardElement> elements, List<ActionBase> actions, RenderContext context)
        {
            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = this.Render(cardElement, context);
                if (uiElement != null)
                {
                    if (grid.RowDefinitions.Count > 0)
                    {
                        var uiSep = new Grid();
                        uiSep.Style = this.GetStyle($"Adaptive.Separator");
                        SeparationOptions sepStyle = null;
                        switch (cardElement.Separation)
                        {
                            case SeparationStyle.None:
                                sepStyle = context.Options.GetElementStyling(cardElement).SeparationNone;
                                break;
                            case SeparationStyle.Default:
                                sepStyle = context.Options.GetElementStyling(cardElement).SeparationDefault;
                                break;

                            case SeparationStyle.Strong:
                                sepStyle = context.Options.GetElementStyling(cardElement).SeparationStrong;
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
                        grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                        Grid.SetRow(uiSep, grid.RowDefinitions.Count - 1);
                        grid.Children.Add(uiSep);
                    }
                    grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    Grid.SetRow(uiElement, grid.RowDefinitions.Count - 1);
                    grid.Children.Add(uiElement);
                }
            }

            if (actions?.Where(a => context.Options.AdaptiveCard.SupportedActions.Contains(a.Type)).Any() == true)
            {
#if WPF
                var uiActionBar = new UniformGrid();
                uiActionBar.Rows = 1;
                uiActionBar.HorizontalAlignment = (System.Windows.HorizontalAlignment)Enum.Parse(typeof(System.Windows.HorizontalAlignment), context.Options.AdaptiveCard.ActionAlignment.ToString());
                uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

                int iCol = 0;
                foreach (var action in actions
                    .Where(a => context.Options.AdaptiveCard.SupportedActions?.Contains(a.Type) == true)
                    .Take(context.Options.AdaptiveCard.MaxActions))
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
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, grid.RowDefinitions.Count - 1);
                grid.Children.Add(uiActionBar);
#elif XAMARIN
                var uiActionBar = new UniformGrid();
                //uiActionBar.Rows = 1;
                //uiActionBar.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                //uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

                int iCol = 0;
                foreach (var action in actions
                    .Where(a => context.Options.AdaptiveCard.SupportedActions?.Contains(a.Type) == true)
                    .Take(context.Options.AdaptiveCard.MaxActions))
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
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, grid.RowDefinitions.Count - 1);
                grid.Children.Add(uiActionBar);
#endif
            }
        }

    }
}