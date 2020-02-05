// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
            context.InputBindings.Add(input.Id, () => uiToggle.GetState() == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false");
            return uiToggle;
        }
    }

}
