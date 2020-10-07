// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveFactSetRenderer
    {
        public static FrameworkElement Render(AdaptiveFactSet factSet, AdaptiveRenderContext context)
        {
            if (factSet.Facts.Count == 0)
            {
                return null;
            }

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
                    MaxWidth = context.Config.FactSet.Title.MaxWidth,
                    Text = fact.Title
                });

                var uiValue = context.Render(new AdaptiveTextBlock()
                {
                    Size = context.Config.FactSet.Value.Size,
                    Color = context.Config.FactSet.Value.Color,
                    IsSubtle = context.Config.FactSet.Value.IsSubtle,
                    Weight = context.Config.FactSet.Value.Weight,
                    Wrap = context.Config.FactSet.Value.Wrap,
                    // MaxWidth is not applicable to the Value field of the Fact
                    // so ignore it.
                    Text = fact.Value
                });

                if (uiTitle != null || uiValue != null)
                {
                    uiFactSet.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                }

                if (uiTitle != null)
                {
                    uiTitle.Style = context.GetStyle("Adaptive.Fact.Title");
                    uiTitle.Margin = new Thickness(left: 0, top: 0, right: context.Config.FactSet.Spacing, bottom: 0);

                    Grid.SetColumn(uiTitle, 0);
                    Grid.SetRow(uiTitle, iRow);
                    uiFactSet.Children.Add(uiTitle);
                }

                if (uiValue != null)
                {
                    uiValue.Style = context.GetStyle("Adaptive.Fact.Value");

                    Grid.SetColumn(uiValue, 1);
                    Grid.SetRow(uiValue, iRow);
                    uiFactSet.Children.Add(uiValue);
                }

                if (uiTitle != null || uiValue != null)
                {
                    iRow++;
                }
            }

            return (iRow == 0) ? null : uiFactSet;
        }
    }
}
