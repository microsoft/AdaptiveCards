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
    public static class XamlFactSet
    {
        public static FrameworkElement Render(TypedElement element, RenderContext context)
        {
            FactSet factSet = (FactSet)element;
            var uiFactSet = new Grid();
            // grid.Margin = factSet.Theme.FactSetMargins;
            uiFactSet.Style = context.GetStyle("Adaptive.FactSet");

            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
            int iRow = 0;
            foreach (var fact in factSet.Facts)
            {
                var uiTitle = context.Render(new TextBlock()
                {
                    Size = context.Options.FactSet.Title.Size,
                    Color = context.Options.FactSet.Title.Color,
                    IsSubtle = context.Options.FactSet.Title.IsSubtle,
                    Weight = context.Options.FactSet.Title.Weight,
                    Wrap = context.Options.FactSet.Title.Wrap,
                    Text = fact.Title
                });
#if WPF
                uiTitle.Style = context.GetStyle("Adaptive.Fact.Title");
                uiTitle.Margin = new Thickness(left: 0, top: 0, right: context.Options.FactSet.Spacing, bottom: 0);
#elif XAMARIN
                //TODO
#endif

                var uiValue = context.Render(new TextBlock()
                {
                    Size = context.Options.FactSet.Value.Size,
                    Color = context.Options.FactSet.Value.Color,
                    IsSubtle = context.Options.FactSet.Value.IsSubtle,
                    Weight = context.Options.FactSet.Value.Weight,
                    Wrap = context.Options.FactSet.Value.Wrap,
                    Text = fact.Value
                });
#if WPF
                uiValue.Style = context.GetStyle("Adaptive.Fact.Value");
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