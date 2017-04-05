using System;
using System.Windows;
using System.Threading.Tasks;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
using UI = System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using UI = Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// FactSet
        /// </summary>
        /// <param name="factSet"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(FactSet factSet, RenderContext context)
        {
            var uiFactSet = new Grid();
            // grid.Margin = this.Theme.FactSetMargins;
            uiFactSet.Style = this.GetStyle("Adaptive.FactSet");

            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            int iRow = 0;
            foreach (var fact in factSet.Facts)
            {
                Tuple<FrameworkElement, FrameworkElement> uiElements = Render(fact, context);
                uiFactSet.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

                Grid.SetColumn(uiElements.Item1, 0);
                Grid.SetRow(uiElements.Item1, iRow);
                uiFactSet.Children.Add(uiElements.Item1);

                Grid.SetColumn(uiElements.Item2, 1);
                Grid.SetRow(uiElements.Item2, iRow++);
                uiFactSet.Children.Add(uiElements.Item2);
            }
            return uiFactSet;
        }


        /// <summary>
        /// Fact
        /// </summary>
        /// <param name="fact"></param>
        /// <returns></returns>
        protected override Tuple<FrameworkElement, FrameworkElement> Render(Fact fact, RenderContext context)
        {
            return new Tuple<FrameworkElement, FrameworkElement>(
                new UI.TextBlock()
                {
                    Text = fact.Title,
                    Style = this.GetStyle("Adaptive.Fact.Title"),
                    Margin = new Thickness(0, 0, 0, 0)
                },
                new UI.TextBlock()
                {
                    Text = fact.Value,
                    Style = this.GetStyle("Adaptive.Fact.Value"),
                    Margin = new Thickness(20, 0, 0, 0)
                }
            );
        }
    }
}