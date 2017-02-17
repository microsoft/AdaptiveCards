using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using Adaptive.Schema.Net;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using ToggleSwitch;
using Xceed.Wpf.Toolkit;

namespace Adaptive.Renderers
{
    public partial class AdaptiveXamlRenderer
    {

        /// <summary>
        /// Input.Text
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected virtual UIElement Render(InputText inputText, List<FrameworkElement> inputControls)
        {
            var textBox = new WatermarkTextBox() { Text = inputText.Value };
            if (inputText.IsMultiline == true)
            {
                textBox.AcceptsReturn = true;
                textBox.TextWrapping = TextWrapping.Wrap;
                textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
            }
            if (inputText.MaxLength.HasValue)
                textBox.MaxLength = inputText.MaxLength.Value;

            textBox.Watermark = inputText.Title;
            textBox.Style = this.GetStyle($"Adaptive.Input.Text.{inputText.Style}");
            textBox.DataContext = inputText;
            inputControls.Add(textBox);
            return textBox;
        }

        /// <summary>
        /// Input.Date
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected virtual UIElement Render(InputDate inputDate, List<FrameworkElement> inputControls)
        {
            var datePicker = new DatePicker();
            datePicker.Text = inputDate.Title;
            DateTime value;
            if (DateTime.TryParse(inputDate.Value, out value))
                datePicker.SelectedDate = value;
            DateTime minValue;
            if (DateTime.TryParse(inputDate.Min, out minValue))
                datePicker.DisplayDateStart = minValue;
            DateTime maxValue;
            if (DateTime.TryParse(inputDate.Max, out maxValue))
                datePicker.DisplayDateEnd = maxValue;
            datePicker.Style = this.GetStyle("Adaptive.Input.Date");
            datePicker.DataContext = inputDate;
            inputControls.Add(datePicker);
            return datePicker;
        }

        /// <summary>
        /// Input.Time
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected virtual UIElement Render(InputTime inputTime, List<FrameworkElement> inputControls)
        {
            var timePicker = new TimePicker();
            DateTime value;
            if (DateTime.TryParse(inputTime.Value, out value))
                timePicker.Value = value;
            TimeSpan minValue;
            if (TimeSpan.TryParse(inputTime.Min, out minValue))
                timePicker.EndTime = minValue;
            TimeSpan maxValue;
            if (TimeSpan.TryParse(inputTime.Max, out maxValue))
                timePicker.EndTime = maxValue;
            timePicker.Watermark = inputTime.Title;
            timePicker.Style = this.GetStyle("Adaptive.Input.Time");
            timePicker.DataContext = inputTime;
            inputControls.Add(timePicker);
            return timePicker;
        }

        /// <summary>
        /// Input.Number
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected virtual UIElement Render(InputNumber inputNumber, List<FrameworkElement> inputControls)
        {
            IntegerUpDown numberPicker = new IntegerUpDown();
            // numberPicker.ShowButtonSpinner = true;

            float value;
            if (float.TryParse(inputNumber.Value, out value))
                numberPicker.Value = Convert.ToInt32(value);

            float minValue;
            if (float.TryParse(inputNumber.Min, out minValue))
                numberPicker.Minimum = Convert.ToInt32(minValue);

            float maxValue;
            if (float.TryParse(inputNumber.Max, out maxValue))
                numberPicker.Maximum = Convert.ToInt32(maxValue);

            numberPicker.Watermark = inputNumber.Title;
            numberPicker.Style = this.GetStyle("Adaptive.Input.Number");
            numberPicker.DataContext = inputNumber;
            inputControls.Add(numberPicker);
            return numberPicker;
        }

        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected virtual UIElement Render(InputToggle inputToggle, List<FrameworkElement> inputControls)
        {
            var toggleSwitch = new HorizontalToggleSwitch();
            toggleSwitch.CheckedContent = inputToggle.Title1;
            toggleSwitch.UncheckedContent = inputToggle.Title2;
            toggleSwitch.IsChecked = inputToggle.Value == inputToggle.Value1;
            toggleSwitch.Style = this.GetStyle($"Adaptive.Input.Toggle");
            toggleSwitch.DataContext = inputToggle;
            inputControls.Add(toggleSwitch);
            return toggleSwitch;
        }

        /// <summary>
        /// Input.ChoiceSet
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected UIElement Render(InputChoiceSet choiceSet, List<FrameworkElement> inputControls)
        {
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
                if (choiceSet.MultiSelect == true)
                {
                    var uiCheckbox = new CheckBox();
                    uiCheckbox.Content = choice.Display;
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
                        uiRadio.GroupName = choiceSet.Id;
                        uiRadio.DataContext = choice;
                        uiRadio.Style = this.GetStyle("Adaptive.Input.ChoiceSet.Radio");
                        uiChoices.Items.Add(uiRadio);
                    }
                }
            }
            if (choiceSet.Style == ChoiceInputStyle.Compact)
            {
                inputControls.Add(uiComboBox);
                return uiComboBox;
            }
            else
            {
                inputControls.Add(uiChoices);
                return uiChoices;
            }
        }

        private dynamic _mergeDataFromControls(dynamic data, List<FrameworkElement> inputControls)
        {
            foreach (var inputControl in inputControls)
            {
                if (inputControl.DataContext is InputChoiceSet)
                {
                    InputChoiceSet choiceInput = (InputChoiceSet)inputControl.DataContext;
                    var value = GetValueFromInputControl(inputControl);
                    if (value != null)
                    {
                        data[choiceInput.Id] = JToken.FromObject(value);
                    }
                }
                else
                {
                    Input input = inputControl.DataContext as Input;
                    var value = GetValueFromInputControl(inputControl);
                    if (value != null)
                    {
                        data[input.Id] = JToken.FromObject(value);
                    }
                }

            }
            return data;
        }

        protected virtual object GetValueFromInputControl(FrameworkElement inputControl)
        {
            if (inputControl is WatermarkTextBox)
            {
                return ((WatermarkTextBox)inputControl).Text;
            }
            else if (inputControl is TextBox)
            {
                return ((TextBox)inputControl).Text;
            }
            else if (inputControl is DatePicker)
            {
                return ((DatePicker)inputControl).Text;
            }
            else if (inputControl is HorizontalToggleSwitch)
            {
                var toggleSwitch = (HorizontalToggleSwitch)inputControl;
                if (toggleSwitch.IsChecked)
                    return ((InputToggle)toggleSwitch.DataContext).Value1;
                else
                    return ((InputToggle)toggleSwitch.DataContext).Value2;
            }
            else if (inputControl is PasswordBox)
            {
                return ((PasswordBox)inputControl).Password;
            }
            else if (inputControl is TimePicker)
            {
                return ((TimePicker)inputControl).Text;
            }
            else if (inputControl is IntegerUpDown)
            {
                return ((IntegerUpDown)inputControl).Text;
            }
            else if (inputControl is ComboBox)
            {
                ComboBox comboBox = (ComboBox)inputControl;
                ComboBoxItem item = comboBox.SelectedItem as ComboBoxItem;
                if (item != null)
                {
                    Choice choice = item.DataContext as Choice;
                    return choice.Value;
                }
                return null;
            }
            else if (inputControl.DataContext is InputChoiceSet)
            {
                InputChoiceSet choiceInput = inputControl.DataContext as InputChoiceSet;
                if (inputControl is ListBox)
                {
                    var choices = inputControl as ListBox;
                    if (choiceInput.MultiSelect == true)
                    {
                        List<string> values = new List<string>();
                        foreach (var item in choices.Items)
                        {
                            CheckBox checkBox = (CheckBox)item;
                            Choice choice = checkBox.DataContext as Choice;
                            if (checkBox.IsChecked == true)
                                values.Add(choice.Value);
                        }
                        return values;
                    }
                    else
                    {
                        foreach (var item in choices.Items)
                        {
                            RadioButton radioBox = (RadioButton)item;
                            Choice choice = radioBox.DataContext as Choice;
                            if (radioBox.IsChecked == true)
                                return choice.Value;
                        }
                        return null;
                    }
                }
            }
            Debug.Print($"Unknown control {inputControl.GetType().Name}");
            return null;
        }

        private void _resetInputControls(List<FrameworkElement> inputControls)
        {
            foreach (var control in inputControls)
            {
                ResetInputControl(control);
            }
        }

        protected virtual void ResetInputControl(FrameworkElement control)
        {
            if (control is TextBox)
            {
                InputText input = control.DataContext as InputText;
                ((TextBox)control).Text = input.Value;
            }
            else if (control is DatePicker)
            {
                InputText input = control.DataContext as InputText;
                ((DatePicker)control).Text = input.Value;
            }
            else if (control is TimePicker)
            {
                InputText input = control.DataContext as InputText;
                ((TimePicker)control).Text = input.Value;
            }
            else if (control is IntegerUpDown)
            {
                InputText input = control.DataContext as InputText;
                ((IntegerUpDown)control).Text = input.Value;
            }
            else if (control is WatermarkTextBox)
            {
                InputText input = control.DataContext as InputText;
                ((WatermarkTextBox)control).Text = input.Value;
            }
            else if (control is HorizontalToggleSwitch)
            {
                InputToggle inputToggle = control.DataContext as InputToggle;
                ((HorizontalToggleSwitch)control).IsChecked = inputToggle.Value == inputToggle.Value1;
            }
            else if (control is PasswordBox)
            {
                InputText input = control.DataContext as InputText;
                ((PasswordBox)control).Password = input.Value;
            }
            else if (control is StackPanel && control.DataContext is InputChoiceSet)
            {
                var stack = control as StackPanel;
                foreach (var child in stack.Children)
                {
                    if (child is CheckBox)
                    {
                        CheckBox checkBox = (CheckBox)child;
                        var choice = checkBox.DataContext as Choice;
                        checkBox.IsChecked = choice.IsSelected == true;
                    }
                    else if (child is RadioButton)
                    {
                        RadioButton radioBox = (RadioButton)child;
                        var choice = radioBox.DataContext as Choice;
                        radioBox.IsChecked = choice.IsSelected == true;
                    }
                }
            }
            else if (control is ComboBox)
            {
                ComboBox comboBox = (ComboBox)control;
                InputChoiceSet choiceInput = comboBox.DataContext as InputChoiceSet;
                comboBox.SelectedIndex = 0;
            }
        }
    }
}