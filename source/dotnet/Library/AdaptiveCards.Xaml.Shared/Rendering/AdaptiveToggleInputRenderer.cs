// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using AdaptiveCards.Xaml.XamarinForms;
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveToggleInputRenderer
    {
        public static FrameworkElement Render(AdaptiveToggleInput input, AdaptiveRenderContext context)
        {
            var uiToggle = new CheckBox();
#if WPF
            AdaptiveChoiceSetRenderer.SetContent(uiToggle, input.Title, input.Wrap);
            uiToggle.Foreground =
                context.GetColorBrush(context.Config.ContainerStyles.Default.ForegroundColors.Default.Default);
#elif XAMARIN

            var grid = new Grid();

            grid.ColumnSpacing = 0;
            grid.RowSpacing = 0;
            grid.Padding = 0;
            grid.Margin = 0;

            grid.ColumnDefinitions = new ColumnDefinitionCollection
                    {
                        new ColumnDefinition() { Width = GridLength.Auto },
                        new ColumnDefinition() { Width = GridLength.Auto }
                    };

            uiToggle.Margin = 0;

            uiToggle.IsChecked = input.Value == (input.ValueOn ?? "true");

            uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");

            uiToggle.SetContext(input);

            Grid.SetColumn(uiToggle, 0);

            grid.Children.Add(uiToggle);

            TextBlock choiceTextBlock = new TextBlock { Text = input.Title, LineBreakMode = LineBreakMode.NoWrap, TextColor = uiToggle.Color };

            choiceTextBlock.Padding = 0;

            choiceTextBlock.Margin = 0;

            choiceTextBlock.VerticalOptions = LayoutOptions.CenterAndExpand;

            uiToggle.Color =
                context.GetColor(context.Config.ContainerStyles.Default.ForegroundColors.Default.Default);

            Grid.SetColumn(choiceTextBlock, 1);

            grid.Children.Add(choiceTextBlock);

            context.InputBindings.Add(input.Id, () => uiToggle.GetState() == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false");

            return grid;
            //AdaptiveChoiceSetRenderer.SetContent(uiToggle, input.Title, input.Wrap);

#endif

#if WPF
            uiToggle.SetState(input.Value == (input.ValueOn ?? "true"));
            uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");
            uiToggle.SetContext(input);
            context.InputBindings.Add(input.Id, () => uiToggle.GetState() == true ? input.ValueOn ?? "true" : input.ValueOff ?? "false");
            return uiToggle;
#endif
        }
    }

}
