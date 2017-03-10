using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Threading.Tasks;

namespace Adaptive
{
    public partial class Container
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<Container, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// Container
        /// </summary>
        /// <param name="container"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            var uiContainer = new Grid();
            uiContainer.Style = context.GetStyle("Adaptive.Container");

            Container.AddContainerElements(uiContainer, this.Items, this.Actions, context);

            if (this.SelectAction != null)
            {
                var uiButton = (Button)this.SelectAction.Render(context.NewActionContext());
                uiButton.Content = uiContainer;
                uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
                return uiButton;
            }

            return uiContainer;
        }

        public static void AddContainerElements(Grid grid, List<CardElement> elements, List<ActionBase> actions, RenderContext context)
        {
            bool hasActions = actions != null && actions.Any();
            if (hasActions)
            {
                // collect our input controls
                context.InputControls = new List<FrameworkElement>();
            }

            foreach (var cardElement in elements)
            {
                // each element has a row
                FrameworkElement uiElement = cardElement.Render(context);
                if (uiElement != null)
                {
                    if (grid.RowDefinitions.Count > 0)
                    {
                        switch (cardElement.Separation)
                        {
                            case SeparationStyle.None:
                                break;
                            case SeparationStyle.Default:
                            case SeparationStyle.Strong:
                                {
                                    var sep = new Separator();
                                    if (cardElement.Separation == SeparationStyle.Default)
                                        sep.Style = context.GetStyle($"Adaptive.Separator.{cardElement.Type}");
                                    else
                                        sep.Style = context.GetStyle($"Adaptive.Separator.Strong");
                                    grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                                    Grid.SetRow(sep, grid.RowDefinitions.Count - 1);
                                    grid.Children.Add(sep);
                                }
                                break;
                        }
                    }
                    grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                    Grid.SetRow(uiElement, grid.RowDefinitions.Count - 1);
                    grid.Children.Add(uiElement);
                }
            }

            if (hasActions)
            {
                var uiActionBar = new UniformGrid();
                uiActionBar.Rows = 1;
                uiActionBar.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

                int iCol = 0;
                foreach (var action in actions)
                {
                    // add actions
                    var uiAction = action.Render(context);
                    if (uiAction != null)
                    {
                        Grid.SetColumn(uiAction, iCol++);
                        uiActionBar.Children.Add(uiAction);
                    }
                }
                uiActionBar.Style = context.GetStyle("Adaptive.Actions");
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, grid.RowDefinitions.Count - 1);
                grid.Children.Add(uiActionBar);
            }
        }

        public override async Task PreRender()
        {
            List<Task> tasks = new List<Task>();
            foreach (var item in this.Items)
                tasks.Add(item.PreRender());

            await Task.WhenAll(tasks.ToArray());
        }

    }
}