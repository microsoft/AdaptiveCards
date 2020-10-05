// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Net.Http.Headers;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveToggleInputRenderer
    {
        public static FrameworkElement Render(AdaptiveToggleInput input, AdaptiveRenderContext context)
        {
            var uiToggle = new CheckBox();
            AdaptiveChoiceSetRenderer.SetContent(uiToggle, input.Title, input.Wrap);
            uiToggle.Foreground =
                context.GetColorBrush(context.Config.ContainerStyles.Default.ForegroundColors.Default.Default);
            uiToggle.SetState(input.Value == (input.ValueOn ?? "true"));
            uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");
            uiToggle.SetContext(input);

            if (input.IsRequired && input.ErrorMessage == null)
            {
                context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.NoWarningForValidatedInput,
                    "Inputs with validation should include an ErrorMessage"));
            }

            context.InputValues.Add(input.Id, new AdaptiveToggleInputValue(input, uiToggle));

            return uiToggle;
        }
    }

}
