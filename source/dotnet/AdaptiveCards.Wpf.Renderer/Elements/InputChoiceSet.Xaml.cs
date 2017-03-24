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
using Xceed.Wpf.Toolkit;
using System.Text;
using System.Windows.Documents;
using System.Collections.Generic;

namespace Adaptive
{
    public partial class InputChoiceSet
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<InputChoiceSet, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// Input.ChoiceSet
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            if (context.Options.SupportInteraction)
            {
                var uiGrid = new Grid();
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });

                var uiComboBox = new ComboBox();
                uiComboBox.Style = context.GetStyle("Adaptive.Input.ChoiceSet.ComboBox");
                uiComboBox.DataContext = this;

                var uiChoices = new ListBox();
                ScrollViewer.SetHorizontalScrollBarVisibility(uiChoices, ScrollBarVisibility.Disabled);
                var itemsPanelTemplate = new ItemsPanelTemplate();
                var factory = new FrameworkElementFactory(typeof(WrapPanel));
                itemsPanelTemplate.VisualTree = factory;
                uiChoices.ItemsPanel = itemsPanelTemplate;
                uiChoices.DataContext = this;
                uiChoices.Style = context.GetStyle("Adaptive.Input.ChoiceSet");

                foreach (var choice in this.Choices)
                {
                    if (this.IsMultiSelect == true)
                    {
                        var uiCheckbox = new CheckBox();
                        uiCheckbox.Content = choice.Title;
                        uiCheckbox.IsChecked = choice.IsSelected;
                        uiCheckbox.DataContext = choice;
                        uiCheckbox.Style = context.GetStyle("Adaptive.Input.ChoiceSet.CheckBox");
                        uiChoices.Items.Add(uiCheckbox);
                    }
                    else
                    {
                        if (this.Style == ChoiceInputStyle.Compact)
                        {
                            var uiComboItem = new ComboBoxItem();
                            uiComboItem.Style = context.GetStyle("Adaptive.Input.ChoiceSet.ComboBoxItem");
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
                            uiRadio.GroupName = this.Id;
                            uiRadio.DataContext = choice;
                            uiRadio.Style = context.GetStyle("Adaptive.Input.ChoiceSet.Radio");
                            uiChoices.Items.Add(uiRadio);
                        }
                    }
                }
                if (this.Style == ChoiceInputStyle.Compact)
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
                string choiceText = GetFallbackText();
                if (choiceText == null)
                {
                    List<string> choices = this.Choices.Select(choice => choice.Title).ToList();
                    if (this.Style == ChoiceInputStyle.Compact)
                    {
                        if (this.IsMultiSelect)
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
                TextBlock tb;
                tb = new TextBlock()
                {
                    Text = choiceText,
                    Wrap = true
                };
                return tb.Render(context);
            }
        }

        private string JoinString(IList<string> choices, string sep, string last)
        {
            StringBuilder sb = new StringBuilder();
            string s = string.Empty;
            for (int i = 0; i < choices.Count - 1; i++)
            {
                sb.Append(s);
                sb.Append(choices[i]);
                s = sep;
            }
            if (choices.Count > 1)
                sb.Append(last);
            sb.Append(choices.Last());
            return sb.ToString();
        }
    }
}