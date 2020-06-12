// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveDateInputRenderer
    {
        public static FrameworkElement Render(AdaptiveDateInput input, AdaptiveRenderContext context)
        {
            var textBox = new TextBox() { Text = input.Value };
            textBox.SetPlaceholder(input.Placeholder);
            textBox.Style = context.GetStyle($"Adaptive.Input.Text.Date");
            textBox.SetContext(input);

            context.InputValues.Add(input.Id, new AdaptiveDateInputValue(input, textBox));

            return textBox;
        }
    }
}
