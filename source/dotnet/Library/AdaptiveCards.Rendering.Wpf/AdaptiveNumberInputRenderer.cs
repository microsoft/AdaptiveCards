// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{

    public static class AdaptiveNumberInputRenderer
    {
        public static FrameworkElement Render(AdaptiveNumberInput input, AdaptiveRenderContext context)
        {
            var textBox = new TextBox() { Text = input.Value.ToString() };
            textBox.SetPlaceholder(input.Placeholder);
            textBox.Style = context.GetStyle($"Adaptive.Input.Text.Number");
            textBox.SetContext(input);

            AdaptiveNumberInputValue numberInputValue = new AdaptiveNumberInputValue(input, textBox);
            context.InputValues.Add(input.Id, numberInputValue);
            context.InputBindings.Add(input.Id, () => numberInputValue.GetValue());

            return textBox;
        }
    }
}
