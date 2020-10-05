// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
using System.Windows.Controls;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class XceedTextInput
    {
        public static FrameworkElement Render(AdaptiveTextInput input, AdaptiveRenderContext context)
        {
            if (context.Config.SupportsInteractivity)
            {
                var textBox = new WatermarkTextBox() { Text = input.Value };
                if (input.IsMultiline == true)
                {
                    textBox.AcceptsReturn = true;
                    textBox.TextWrapping = TextWrapping.Wrap;
                    textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
                }
                if (input.MaxLength > 0)
                {
                    textBox.MaxLength = input.MaxLength;
                }

                textBox.Watermark = input.Placeholder;
                textBox.Style = context.GetStyle($"Adaptive.Input.Text.{input.Style}");
                textBox.DataContext = input;

                if ((input.IsRequired || input.Regex != null) && input.ErrorMessage == null)
                {
                    context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.NoWarningForValidatedInput,
                        "Inputs with validation should include an ErrorMessage"));
                }

                context.InputValues.Add(input.Id, new AdaptiveXceedTextInputValue(input, textBox));

                if (input.InlineAction != null)
                {
                    if (context.Config.Actions.ShowCard.ActionMode == ShowCardActionMode.Inline &&
                        input.InlineAction.GetType() == typeof(AdaptiveShowCardAction))
                    {
                        context.Warnings.Add(new AdaptiveWarning(-1, "Inline ShowCard not supported for InlineAction"));
                    }
                    else
                    {
                        if (context.Config.SupportsInteractivity && context.ActionHandlers.IsSupported(input.InlineAction.GetType()))
                        {
                            return AdaptiveTextInputRenderer.RenderInlineAction(input, context, textBox);
                        }
                    }
                }
                return textBox;
            }
            else
            {
                var textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                textBlock.Text = XamlUtilities.GetFallbackText(input) ?? input.Placeholder;

                context.InputValues.Add(input.Id, new AdaptiveXceedTextInputValue(input, null));

                return context.Render(textBlock);
            }
        }
    }
}
