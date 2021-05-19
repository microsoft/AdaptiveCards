// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveChoiceSetRenderer
    {
        public static FrameworkElement Render(AdaptiveChoiceSetInput input, AdaptiveRenderContext context)
        {
            return RenderHelper(new Grid(), new ComboBox(), new StackPanel(), input, context);
        }

        public static void ToggleVisibility(
            FrameworkElement uiElement,
            AdaptiveAction inlineAction,
            AdaptiveRenderContext context)
        {
            if (inlineAction is AdaptiveToggleVisibilityAction iAction)
            {
                context.InvokeAction(uiElement, new AdaptiveActionEventArgs(iAction));
            }
        }

        public static void ForceToggleVisibility(
            FrameworkElement uiElement,
            AdaptiveAction inlineAction,
            AdaptiveRenderContext context,
            bool isVisible)
        {
            if (inlineAction is AdaptiveToggleVisibilityAction iAction)
            {
                iAction.TargetElements =
                    iAction.TargetElements.Select(o =>
                    {
                        o.IsVisible = isVisible;
                        return o;
                    }).ToList();

                context.InvokeAction(uiElement, new AdaptiveActionEventArgs(iAction));
            }
        }

        public static FrameworkElement RenderHelper(Grid uiGrid, ComboBox uiComboBox, StackPanel uiChoices, AdaptiveChoiceSetInput input, AdaptiveRenderContext context)
        {
            var chosen = input.Value?.Split(',').Select(p => p.Trim()).Where(s => !string.IsNullOrEmpty(s)).ToList() ?? new List<string>();

            uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            uiGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });

            uiComboBox.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.ComboBox");
            uiComboBox.DataContext = input;

            uiChoices.DataContext = input;
            uiChoices.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput");

            foreach (var choice in input.Choices)
            {
                if (input.IsMultiSelect == true)
                {
                    var uiCheckbox = new CheckBox();
                    SetContent(uiCheckbox, choice.Title, input.Wrap);
                    uiCheckbox.IsChecked = chosen.Contains(choice.Value);
                    uiCheckbox.DataContext = choice;
                    uiCheckbox.IsEnabled = choice.IsEnabled;
                    uiCheckbox.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.CheckBox");
                    uiChoices.Children.Add(uiCheckbox);

                    uiCheckbox.Checked += (sender, e) =>
                    {
                        ForceToggleVisibility(
                            uiCheckbox,
                            choice.InlineAction,
                            context,
                            true);

                        e.Handled = true;
                    };

                    uiCheckbox.Unchecked += (sender, e) =>
                    {
                        ForceToggleVisibility(
                            uiCheckbox,
                            choice.InlineAction,
                            context,
                            false);

                        e.Handled = true;
                    };
                }
                else
                {
                    if (input.Style == AdaptiveChoiceInputStyle.Compact)
                    {
                        var uiComboItem = new ComboBoxItem();
                        uiComboItem.HorizontalAlignment = HorizontalAlignment.Stretch;
                        uiComboItem.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.ComboBoxItem");

                        TextBlock content = SetContent(uiComboItem, choice.Title, input.Wrap);
                        // The content TextBlock is binded to the width of the comboBox container
                        if (input.Wrap && content != null)
                        {
                            BindingOperations.SetBinding(content, TextBlock.MaxWidthProperty,
                                new Binding("ActualWidth") { Source = uiComboBox });
                        }

                        uiComboItem.DataContext = choice;
                        
                        uiComboBox.Items.Add(uiComboItem);

                        // If multiple values are specified, no option is selected
                        if (chosen.Contains(choice.Value) && chosen.Count == 1)
                        {
                            uiComboBox.SelectedItem = uiComboItem;
                        }

                        uiComboItem.Selected += (sender, e) =>
                        {
                            ToggleVisibility(
                                uiComboItem,
                                choice.InlineAction,
                                context);

                            e.Handled = true;
                        };
                    }
                    else
                    {
                        var uiRadio = new RadioButton();
                        SetContent(uiRadio, choice.Title, input.Wrap);

                        // When isMultiSelect is false, only 1 specified value is accepted.
                        // Otherwise, don't set any option
                        if (chosen.Count == 1)
                        {
                            uiRadio.IsChecked = chosen.Contains(choice.Value);
                        }
                        uiRadio.GroupName = input.Id;
                        uiRadio.DataContext = choice;
                        uiRadio.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.Radio");
                        uiChoices.Children.Add(uiRadio);

                        uiRadio.Checked += (sender, e) =>
                        {
                            ToggleVisibility(
                                uiRadio,
                                choice.InlineAction,
                                context);

                            e.Handled = true;
                        };
                    }
                }
            }

            AdaptiveChoiceSetInputValue inputValue = null;
            
            if (!input.IsMultiSelect && input.Style == AdaptiveChoiceInputStyle.Compact)
            {
                Grid.SetRow(uiComboBox, 1);
                uiGrid.Children.Add(uiComboBox);
                inputValue = new AdaptiveChoiceSetInputValue(input, uiComboBox);
            }
            else
            {
                Grid.SetRow(uiChoices, 1);
                uiGrid.Children.Add(uiChoices);
                inputValue = new AdaptiveChoiceSetInputValue(input, uiChoices, uiChoices.Children[0]);
            }

            if (input.IsRequired && string.IsNullOrEmpty(input.ErrorMessage))
            {
                context.Warnings.Add(new AdaptiveWarning((int)AdaptiveWarning.WarningStatusCode.NoErrorMessageForValidatedInput,
                    "Inputs with validation should include an ErrorMessage"));
            }

            context.InputValues.Add(input.Id, inputValue);

            return uiGrid;
        }

        public static TextBlock SetContent(ContentControl uiControl, string text, bool wrap)
        {
            if (wrap)
            {
                TextBlock wrappedTextBlock = new TextBlock { Text = text, TextWrapping = TextWrapping.Wrap };
                uiControl.Content = wrappedTextBlock;
                return wrappedTextBlock;
            }
            else
            {
                uiControl.Content = text;
            }
            return null;
        }
    }
}
