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

                IntegerUpDown numberPicker = new IntegerUpDown();
                // numberPicker.ShowButtonSpinner = true;

                if (!Double.IsNaN(input.Value))
                    numberPicker.Value = Convert.ToInt32(input.Value);

                if (!Double.IsNaN(input.Min))
                    numberPicker.Minimum = Convert.ToInt32(input.Min);

                if (!Double.IsNaN(input.Max))
                    numberPicker.Maximum = Convert.ToInt32(input.Max);

                numberPicker.Watermark = input.Placeholder;
                numberPicker.Style = context.GetStyle("Adaptive.Input.Number");
                numberPicker.DataContext = input;
                context.InputBindings.Add(input.Id, () => numberPicker.Value?.ToString());
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
