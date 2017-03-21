using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Adaptive
{
    public partial class Container
    {
      

        /// <summary>
        /// Container
        /// </summary>
        /// <param name="container"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
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
                if (cardElement is Container && grid.RowDefinitions.Count > 0)
                {
                    Container container = (Container)cardElement;
                    if (container.StartGroup == true)
                    {
                        var sep = new Separator();
                        grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                        Grid.SetRow(sep, grid.RowDefinitions.Count - 1);
                        sep.Style = context.GetStyle("Adaptive.Separator");
                        grid.Children.Add(sep);
                    }
                }
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiElement, grid.RowDefinitions.Count - 1);
                grid.Children.Add(uiElement);
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
                    Grid.SetColumn(uiAction, iCol++);
                    uiActionBar.Children.Add(uiAction);
                }
                uiActionBar.Style = context.GetStyle("Adaptive.Actions");
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, grid.RowDefinitions.Count - 1);
                grid.Children.Add(uiActionBar);
            }
        }

    }
}