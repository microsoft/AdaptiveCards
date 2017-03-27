using System;
using System.Linq;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using System.Text;
using System.Windows.Documents;
using System.Collections.Generic;

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// Input.ChoiceSet
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(InputChoiceSet choiceSet, RenderContext context)
        {
     
            if (this.Options.SupportInteraction)
            {
                var uiGrid = new Grid();
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });

                var uiComboBox = new ComboBox();
                uiComboBox.Style = this.GetStyle("Adaptive.Input.ChoiceSet.ComboBox");
                uiComboBox.DataContext = choiceSet;

                var uiChoices = new ListBox();
                ScrollViewer.SetHorizontalScrollBarVisibility(uiChoices, ScrollBarVisibility.Disabled);
                var itemsPanelTemplate = new ItemsPanelTemplate();
                var factory = new FrameworkElementFactory(typeof(WrapPanel));
                itemsPanelTemplate.VisualTree = factory;
                uiChoices.ItemsPanel = itemsPanelTemplate;
                uiChoices.DataContext = choiceSet;
                uiChoices.Style = this.GetStyle("Adaptive.Input.ChoiceSet");

                foreach (var choice in choiceSet.Choices)
                {
                    if (choiceSet.IsMultiSelect == true)
                    {
                        var uiCheckbox = new CheckBox();
                        uiCheckbox.Content = choice.Title;
                        uiCheckbox.IsChecked = choice.IsSelected;
                        uiCheckbox.DataContext = choice;
                        uiCheckbox.Style = this.GetStyle("Adaptive.Input.ChoiceSet.CheckBox");
                        uiChoices.Items.Add(uiCheckbox);
                    }
                    else
                    {
                        if (choiceSet.Style == ChoiceInputStyle.Compact)
                        {
                            var uiComboItem = new ComboBoxItem();
                            uiComboItem.Style = this.GetStyle("Adaptive.Input.ChoiceSet.ComboBoxItem");
                            uiComboItem.Content = choice.Title;
                            uiComboItem.DataContext = choice;
                            uiComboBox.Items.Add(uiComboItem);
                            if (choice.IsSelected)
                                uiComboBox.SelectedItem = uiComboItem;
                        }
                        else
                        {
                            var uiRadio = new RadioButton();
                            uiRadio.Content = choice.Title;
                            uiRadio.IsChecked = choice.IsSelected;
                            uiRadio.GroupName = choiceSet.Id;
                            uiRadio.DataContext = choice;
                            uiRadio.Style = this.GetStyle("Adaptive.Input.ChoiceSet.Radio");
                            uiChoices.Items.Add(uiRadio);
                        }
                    }
                }
                if (choiceSet.Style == ChoiceInputStyle.Compact)
                {
                    context.InputControls.Add(uiComboBox);
                    Grid.SetRow(uiComboBox, 1);
                    uiGrid.Children.Add(uiComboBox);
                    return uiGrid;
                }
                else
                {
                    context.InputControls.Add(uiChoices);
                    Grid.SetRow(uiChoices, 1);
                    uiGrid.Children.Add(uiChoices);
                    return uiGrid;
                }
            }
            else
            {
                string choiceText = this.GetFallbackText(choiceSet);
                if (choiceText == null)
                {
                    List<string> choices = choiceSet.Choices.Select(choice => choice.Title).ToList();
                    if (choiceSet.Style == ChoiceInputStyle.Compact)
                    {
                        if (choiceSet.IsMultiSelect)
                        {
                            choiceText = $"Choices: {JoinString(choices, ", ", " and ")}";
                        }
                        else
                        {
                            choiceText = $"Choices: {JoinString(choices, ", ", " or ")}";
                        }
                    }
                    else // if (this.Style == ChoiceInputStyle.Expanded)
                    {
                        choiceText = $"* {JoinString(choices, "\n* ", "\n* ")}";
                    }
                }
                Container container = new Container() { Separation = choiceSet.Separation };
                container.Items.Add(new TextBlock()
                {
                    Text = choiceText,
                    Wrap = true
                });
                container.Items.Add(new TextBlock()
                {
                    Text = JoinString(choiceSet.Choices.Where(c => c.IsSelected).Select(c => c.Title).ToList(), ", ", " and "),
                    Color = TextColor.Accent,
                    Wrap = true
                });
                return Render(container, context);
            }
        }

    }
}