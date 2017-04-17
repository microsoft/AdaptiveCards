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
    public static class XamlFactSet
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            FactSet factSet = (FactSet)element;
            var uiFactSet = new Grid();
            // grid.Margin = factSet.Theme.FactSetMargins;
            uiFactSet.Style = context.GetStyle("Adaptive.FactSet");

            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            int iRow = 0;
            foreach (var fact in factSet.Facts)
            {
                var uiTitle = context.Render(new TextBlock()
                {
                    Size = context.Options.FactSet.Title.Size,
                    Color = context.Options.FactSet.Title.Color,
                    IsSubtle = context.Options.FactSet.Title.IsSubtle,
                    Weight = context.Options.FactSet.Title.Weight,
                    Text = fact.Title
                });
#if WPF
                uiTitle.Style = context.GetStyle("Adaptive.Fact.Title");
#elif XAMARIN
                //TODO
#endif

                var uiValue = context.Render(new TextBlock()
                {
                    Size = context.Options.FactSet.Value.Size,
                    Color = context.Options.FactSet.Value.Color,
                    IsSubtle = context.Options.FactSet.Value.IsSubtle,
                    Weight = context.Options.FactSet.Value.Weight,
                    Text = fact.Value
                });
#if WPF
                uiValue.Style = context.GetStyle("Adaptive.Fact.Value");
                uiValue.Margin = new Thickness(context.Options.FactSet.Spacing, 0, 0, 0);
#elif XAMARIN
                //TODO
#endif

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