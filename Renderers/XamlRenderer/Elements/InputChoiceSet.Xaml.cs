using System;
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

namespace Adaptive
{
    public partial class InputChoiceSet
    {

        /// <summary>
        /// Input.ChoiceSet
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
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
                    uiCheckbox.Content = choice.Display;
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
                        uiComboItem.Content = choice.Display;
                        uiComboItem.DataContext = choice;
                        uiComboBox.Items.Add(uiComboItem);
                        if (choice.IsSelected)
                            uiComboBox.SelectedItem = uiComboItem;
                    }
                    else
                    {
                        var uiRadio = new RadioButton();
                        uiRadio.Content = choice.Display;
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
    }

}