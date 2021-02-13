// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering.Wpf
{

    public static class XceedNumberInput
    {
        public static FrameworkElement Render(AdaptiveNumberInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {

                DoubleUpDown numberPicker = new DoubleUpDown();

                if (!Double.IsNaN(input.Value))
                    numberPicker.Value = input.Value;

                numberPicker.Watermark = input.Placeholder;
                numberPicker.Style = context.GetStyle("Adaptive.Input.Number");
                numberPicker.DataContext = input;

                numberPicker.Maximum = input.Max;
                numberPicker.Minimum = input.Min;

                if (input.IsRequired && string.IsNullOrEmpty(input.ErrorMessage))
                {
                    context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.NoErrorMessageForValidatedInput, "Inputs with validation should include an ErrorMessage"));
                }

                context.InputValues.Add(input.Id, new AdaptiveXceedNumberInputValue(input, numberPicker));

                return numberPicker;
            }
            else
            {
                var textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;
                return context.Render(textBlock);
            }

        }
    }
}
