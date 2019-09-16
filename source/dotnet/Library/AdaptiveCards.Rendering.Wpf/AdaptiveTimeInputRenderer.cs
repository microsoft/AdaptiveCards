// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveTimeInputRenderer
    {
        public static FrameworkElement Render(AdaptiveTimeInput input, AdaptiveRenderContext context)
        {
            var textBox = new TextBox() { Text = input.Value };
            textBox.SetPlaceholder(input.Placeholder);
            textBox.Style = context.GetStyle("Adaptive.Input.Text.Time");
            textBox.SetContext(input);
            context.InputBindings.Add(input.Id, () => textBox.Text);
            return textBox;
        }
    }
}
