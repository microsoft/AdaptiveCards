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
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
    {
        public static FrameworkElement RenderFactSet(TypedElement element, RenderContext context)
        {
            FactSet factSet = (FactSet)element;
            var uiFactSet = new Grid();
            // grid.Margin = this.Theme.FactSetMargins;
            uiFactSet.Style = context.GetStyle("Adaptive.FactSet");

            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            int iRow = 0;
            foreach (var fact in factSet.Facts)
            {
                var uiTitle = new UI.TextBlock()
                {
                    Text = fact.Title,
                    Style = context.GetStyle("Adaptive.Fact.Title"),
                    Margin = new Thickness(0, 0, 0, 0)
                };
                var uiValue = new UI.TextBlock()
                {
                    Text = fact.Value,
                    Style = context.GetStyle("Adaptive.Fact.Value"),
                    Margin = new Thickness(20, 0, 0, 0)
                };
                uiFactSet.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

                Grid.SetColumn(uiTitle, 0);
                Grid.SetRow(uiTitle, iRow);
                uiFactSet.Children.Add(uiTitle);

                Grid.SetColumn(uiValue, 1);
                Grid.SetRow(uiValue, iRow++);
                uiFactSet.Children.Add(uiValue);
            }
            return uiFactSet;
        }
    }
}