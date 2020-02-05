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
        public static FrameworkElement Render(AdaptiveTypedElement element, RenderContext context)
        {
            AdaptiveFactSet factSet = (AdaptiveFactSet)element;
            var uiFactSet = new Grid();
            // grid.Margin = factSet.Theme.FactSetMargins;
            uiFactSet.Style = context.GetStyle("Adaptive.FactSet");

            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
            int iRow = 0;
            foreach (var fact in factSet.Facts)
            {
                var uiTitle = context.Render(new AdaptiveTextBlock()
                {
                    Size = context.Config.FactSet.Title.Size,
                    Color = context.Config.FactSet.Title.Color,
                    IsSubtle = context.Config.FactSet.Title.IsSubtle,
                    Weight = context.Config.FactSet.Title.Weight,
                    Wrap = context.Config.FactSet.Title.Wrap,
                    Text = fact.Title
                });
#if WPF
                uiTitle.Style = context.GetStyle("Adaptive.Fact.Title");
                uiTitle.Margin = new Thickness(left: 0, top: 0, right: context.Config.FactSet.Spacing, bottom: 0);
#elif XAMARIN
                //TODO
#endif

                var uiValue = context.Render(new AdaptiveTextBlock()
                {
                    Size = context.Config.FactSet.Value.Size,
                    Color = context.Config.FactSet.Value.Color,
                    IsSubtle = context.Config.FactSet.Value.IsSubtle,
                    Weight = context.Config.FactSet.Value.Weight,
                    Wrap = context.Config.FactSet.Value.Wrap,
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
