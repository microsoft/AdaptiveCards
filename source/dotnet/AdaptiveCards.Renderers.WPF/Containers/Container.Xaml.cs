using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Threading.Tasks;
#if WPF
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif Xamarin
using Xamarin.Forms;
using Button = AdaptiveCards.XamarinForms.Renderer.ContentButton;
#endif

namespace AdaptiveCards.Renderers
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
                        switch (cardElement.Separation)
                        {
                            case SeparationStyle.None:
                                break;
                            case SeparationStyle.Default:
                            case SeparationStyle.Strong:
                                {
                                    var sep = new Separator();
                                    if (cardElement.Separation == SeparationStyle.Default)
                                        sep.Style = this.GetStyle($"Adaptive.Separator.{cardElement.Type}");
                                    else
                                        sep.Style = this.GetStyle($"Adaptive.Separator.Strong");
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

            if (actions?.Any() == true)
            {
#if WPF
                var uiActionBar = new UniformGrid();
                uiActionBar.Rows = 1;
                uiActionBar.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

                int iCol = 0;
                foreach (var action in actions)
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
#elif Xamarin
                // TODO: Action bar
#endif
            }
        }

    }
}