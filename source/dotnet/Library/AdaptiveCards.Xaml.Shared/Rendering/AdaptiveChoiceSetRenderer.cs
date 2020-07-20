// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Xml;
using System.Windows;
#if WPF
using System.Windows.Media;
using System.Windows.Data;
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveChoiceSetRenderer
    {
        public static FrameworkElement Render(AdaptiveChoiceSetInput input, AdaptiveRenderContext context)
        {
            var chosen = input.Value?.Split(',').Select(p => p.Trim()).Where(s => !string.IsNullOrEmpty(s)).ToList() ?? new List<string>();

# if WPF
            var uiGrid = new Grid();
            uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            uiGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });

            var uiComboBox = new ComboBox();
            uiComboBox.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.ComboBox");
            uiComboBox.DataContext = input;

            var uiChoices = new StackPanel();
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
                    uiCheckbox.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.CheckBox");
                    uiChoices.Children.Add(uiCheckbox);
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
                    }
                }
            }
            context.InputBindings.Add(input.Id, () =>
            {
                if (input.IsMultiSelect == true)
                {
                    string values = string.Empty;
                    foreach (var item in uiChoices.Children)
                    {
                        CheckBox checkBox = (CheckBox)item;
                        AdaptiveChoice adaptiveChoice = checkBox.DataContext as AdaptiveChoice;
                        if (checkBox.IsChecked == true)
                            values += (values == string.Empty ? "" : ",") + adaptiveChoice.Value;
                    }
                    return values;
                }
                else
                {
                    if (input.Style == AdaptiveChoiceInputStyle.Compact)
                    {
                        ComboBoxItem item = uiComboBox.SelectedItem as ComboBoxItem;
                        if (item != null)
                        {
                            AdaptiveChoice adaptiveChoice = item.DataContext as AdaptiveChoice;
                            return adaptiveChoice.Value;
                        }
                        return null;
                    }
                    else
                    {
                        foreach (var item in uiChoices.Children)
                        {
                            RadioButton radioBox = (RadioButton)item;
                            AdaptiveChoice adaptiveChoice = radioBox.DataContext as AdaptiveChoice;
                            if (radioBox.IsChecked == true)
                                return adaptiveChoice.Value;
                        }
                        return null;
                    }
                }
            });

            if (!input.IsMultiSelect && input.Style == AdaptiveChoiceInputStyle.Compact)
            {
                Grid.SetRow(uiComboBox, 1);
                uiGrid.Children.Add(uiComboBox);
                return uiGrid;
            }
            else
            {
                Grid.SetRow(uiChoices, 1);
                uiGrid.Children.Add(uiChoices);
                return uiGrid;
            }
# endif

            if (input.IsMultiSelect)
            {
                StackLayout stackLayout = new StackLayout
                {
                };

                foreach (var choice in input.Choices)
                {
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

                    var uiCheckbox = new CheckBox();

                    uiCheckbox.Margin = 0;

                    uiCheckbox.IsChecked = chosen.Contains(choice.Value);

                    uiCheckbox.BindingContext = choice;

                    uiCheckbox.Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.CheckBox");

                    Grid.SetColumn(uiCheckbox, 0);

                    grid.Children.Add(uiCheckbox);

                    TextBlock choiceTextBlock = new TextBlock { Text = choice.Title, LineBreakMode = LineBreakMode.NoWrap, TextColor = uiCheckbox.Color };

                    choiceTextBlock.Padding = 0;

                    choiceTextBlock.Margin = 0;

                    choiceTextBlock.VerticalOptions = LayoutOptions.CenterAndExpand;

                    Grid.SetColumn(choiceTextBlock, 1);

                    grid.Children.Add(choiceTextBlock);

                    stackLayout.Children.Add(grid);
                }

                return stackLayout;
            }
            else if (input.Style == AdaptiveChoiceInputStyle.Expanded)
            {
                StackLayout stackLayout = new StackLayout
                {
                };

                foreach (var choice in input.Choices)
                {
                    var radio = new RadioButton
                    {
                        Text = choice.Title,
                        IsChecked = choice.IsSelected,
                        BindingContext = choice,
                        GroupName = input.Id,
                        Style = context.GetStyle("Adaptive.Input.AdaptiveChoiceSetInput.Radio")
                    };

                    stackLayout.Children.Add(radio);
                }

                return stackLayout;
            }
            else
            {
                //Compact
            }

            
            string choiceText = "";// XamlUtilities.GetFallbackText(input);
            if (choiceText == null)
            {
                List<string> choices = input.Choices.Select(choice => choice.Title).ToList();
                if (input.Style == AdaptiveChoiceInputStyle.Compact)
                {
                    if (input.IsMultiSelect)
                    {
                        choiceText = $"Choices: {RendererUtilities.JoinString(choices, ", ", " and ")}";
                    }
                    else
                    {
                        choiceText = $"Choices: {RendererUtilities.JoinString(choices, ", ", " or ")}";
                    }
                }
                else // if (choiceSet.Style == ChoiceInputStyle.Expanded)
                {
                    choiceText = $"* {RendererUtilities.JoinString(choices, "\n* ", "\n* ")}";
                }
            }
            AdaptiveContainer container = AdaptiveTypedElementConverter.CreateElement<AdaptiveContainer>();
            container.Spacing = input.Spacing;
            container.Separator = input.Separator;
            AdaptiveTextBlock textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
            textBlock.Text = choiceText;
            textBlock.Wrap = true;
            container.Items.Add(textBlock);

            textBlock = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
            textBlock.Text = RendererUtilities.JoinString(input.Choices.Where(c => c.IsSelected).Select(c => c.Title).ToList(), ", ", " and ");
            textBlock.Color = AdaptiveTextColor.Accent;
            textBlock.Wrap = true;
            container.Items.Add(textBlock);
            return context.Render(container);
        }

#if WPF
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
#elif XAMARIN
        public static TextBlock SetContent(ContentView uiControl, string text, bool wrap)
        {
            TextBlock wrappedTextBlock = new TextBlock { Text = text, LineBreakMode =  wrap ? LineBreakMode.WordWrap : LineBreakMode.NoWrap };
            uiControl.Content = wrappedTextBlock;
            return wrappedTextBlock;
        }
#endif
    }
}
