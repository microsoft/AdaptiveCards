// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
using System.Windows.Controls;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveColorInputRenderer
    {
        public static FrameworkElement Render(AdaptiveColorInput input, AdaptiveRenderContext context)
        {
            var grid = new Grid();

            ColorCanvas colorPicker = new ColorCanvas();

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
            Grid.SetColumn(colorPicker, 0);
            grid.Children.Add(colorPicker);

            context.InputValues.Add($"{input.Id}", new AdaptiveColorInputValue(input, colorPicker));

            return grid;
        }
    }
}
