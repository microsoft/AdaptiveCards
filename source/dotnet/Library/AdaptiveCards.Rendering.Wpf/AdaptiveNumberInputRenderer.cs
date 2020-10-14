// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{

    public static class AdaptiveNumberInputRenderer
    {
        public static FrameworkElement Render(AdaptiveNumberInput input, AdaptiveRenderContext context)
        {
            var textBox = new TextBox();

            if (!Double.IsNaN(input.Value))
            {
                textBox.Text = input.Value.ToString();
            }
            textBox.SetPlaceholder(input.Placeholder);
            textBox.Style = context.GetStyle($"Adaptive.Input.Text.Number");
            textBox.SetContext(input);

            if ((!Double.IsNaN(input.Max) || !Double.IsNaN(input.Min) || input.IsRequired)
                && input.ErrorMessage == null)
            {
                context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.NoWarningForValidatedInput,
                    "Inputs with validation should include an ErrorMessage"));
            }

            context.InputValues.Add(input.Id, new AdaptiveNumberInputValue(input, textBox));

            return textBox;
        }
    }
}
