// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Net.Http.Headers;
using System.Windows;
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

            AdaptiveToggleInputValue toggleInputValue = new AdaptiveToggleInputValue(input, uiToggle);
            context.InputValues.Add(input.Id, toggleInputValue);
            context.InputBindings.Add(input.Id, () => toggleInputValue.GetValue());

            return uiToggle;
        }
    }

}
