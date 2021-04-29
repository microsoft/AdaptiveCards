// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.Win32;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveFileInputRenderer
    {
        public static FrameworkElement Render(AdaptiveFileInput input, AdaptiveRenderContext context)
        {
            var grid = new Grid();

            var textBox = new TextBox() { Text = input.Value };

            var button = new Button();
            Style style = context.GetStyle($"Adaptive.Input.Text.InlineAction.Button");
            if (style != null)
            {
                button.Style = style;
            }

            if (input.MaxLength > 0)
            {
                textBox.MaxLength = input.MaxLength;
            }

            textBox.SetPlaceholder(input.Placeholder);
            textBox.Style = context.GetStyle($"Adaptive.Input.Text.{input.Style}");
            textBox.SetContext(input);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
            Grid.SetColumn(textBox, 0);
            grid.Children.Add(textBox);

            int spacing = context.Config.GetSpacing(AdaptiveSpacing.Default);
            var uiSep = new Grid
            {
                Style = context.GetStyle($"Adaptive.Input.Text.InlineAction.Separator"),
                VerticalAlignment = VerticalAlignment.Stretch,
                Width = spacing,
            };

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(spacing, GridUnitType.Pixel) });
            Grid.SetColumn(uiSep, 1);

            button.Click += (sender, e) =>
            {
                // FILE
                OpenFileDialog openFileDialog = new OpenFileDialog();

                if (openFileDialog.ShowDialog() == true)
                {
                    textBox.Text = openFileDialog.FileName;
                }

                // Prevent nested events from triggering
                e.Handled = true;
            };

            var uiTitle = new TextBlock
            {
                Text = "Upload"
            };

            uiTitle.FontSize = context.Config.GetFontSize(AdaptiveFontType.Default, AdaptiveTextSize.Default);
            uiTitle.Style = context.GetStyle($"Adaptive.Input.Text.InlineAction.Title");
            button.Content = uiTitle;

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            Grid.SetColumn(button, 2);
            grid.Children.Add(button);
            button.VerticalAlignment = VerticalAlignment.Bottom;

            if ((input.IsRequired || input.Regex != null) && string.IsNullOrEmpty(input.ErrorMessage))
            {
                context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.NoErrorMessageForValidatedInput,
                    "Inputs with validation should include an ErrorMessage"));
            }

            context.InputValues.Add($"{input.Id}", new AdaptiveFileInputValue(input, textBox));

            return grid;
        }
    }
}
