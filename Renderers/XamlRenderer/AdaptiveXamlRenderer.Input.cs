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

namespace Adaptive.Renderers
{
    public partial class AdaptiveXamlRenderer
    {

        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public virtual UIElement Render(TextInput textInput, List<FrameworkElement> inputControls)
        {
            if (textInput.Style.HasValue)
            {
                switch (textInput.Style)
                {
                    case TextInputStyle.Date:
                        {
                            var datePicker = new DatePicker();
                            DateTime value;
                            if (DateTime.TryParse(textInput.Value, out value))
                                datePicker.SelectedDate = value;
                            DateTime minValue;
                            if (DateTime.TryParse(textInput.Min, out minValue))
                                datePicker.DisplayDateStart = minValue;
                            DateTime maxValue;
                            if (DateTime.TryParse(textInput.Max, out maxValue))
                                datePicker.DisplayDateEnd = maxValue;
                            datePicker.Style = this.GetStyle("Adaptive.Input.TextInput.Date");
                            datePicker.DataContext = textInput;
                            inputControls.Add(datePicker);
                            return datePicker;
                        }

                    case TextInputStyle.Password:
                        {
                            PasswordBox passwordBox = new PasswordBox() { Password = textInput.Value };

                            if (textInput.MaxLength.HasValue)
                                passwordBox.MaxLength = textInput.MaxLength.Value;

                            passwordBox.Style = this.GetStyle("Adaptive.Input.TextInput.Password");
                            passwordBox.DataContext = textInput;
                            inputControls.Add(passwordBox);
                            return passwordBox;
                        }

                    case TextInputStyle.Range:
                        {
                            var rangeGrid = new Grid();
                            rangeGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                            rangeGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                            rangeGrid.Style = this.GetStyle("Adapative.Input.TextInput.Range");

                            var rangePanel = new StackPanel();
                            rangePanel.Orientation = Orientation.Horizontal;
                            Grid.SetColumn(rangePanel, 1);

                            Slider slider = new Slider();
                            slider.IsSnapToTickEnabled = true;
                            slider.TickPlacement = TickPlacement.BottomRight;
                            double min;
                            if (double.TryParse(textInput.Min, out min))
                                slider.Minimum = min;
                            double max;
                            if (double.TryParse(textInput.Max, out max))
                                slider.Maximum = max;
                            double val;
                            if (double.TryParse(textInput.Value, out val))
                                slider.Value = val;
                            float step;
                            if (float.TryParse(textInput.Step, out step))
                            {
                                slider.SmallChange = Convert.ToInt32(step);
                                slider.LargeChange = 2 * Convert.ToInt32(step);
                            }
                            rangeGrid.Children.Add(slider);

                            TextBox tb = new TextBox();
                            tb.VerticalAlignment = VerticalAlignment.Center;
                            tb.Style = this.GetStyle("Adaptive.Input.TextInput.Range.TextBox");
                            tb.DataContext = textInput;
                            inputControls.Add(tb);
                            rangePanel.Children.Add(tb);

                            tb.SetBinding(TextBox.TextProperty, new Binding()
                            {
                                Path = new PropertyPath("Value"),
                                Source = slider,
                                Mode = BindingMode.TwoWay
                            });
                            rangeGrid.Children.Add(rangePanel);
                            return rangeGrid;
                        }
                    case TextInputStyle.Datetime:
                    case TextInputStyle.Time:
                    case TextInputStyle.Number:
                    case TextInputStyle.Tel:
                    case TextInputStyle.Email:
                    case TextInputStyle.Month:
                    case TextInputStyle.Week:
                    default:
                        break;
                }
            }

            var textBox = new TextBox() { Text = textInput.Value };
            if (textInput.IsMultiline == true)
            {
                textBox.AcceptsReturn = true;
                textBox.TextWrapping = TextWrapping.Wrap;
                textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
            }
            if (textInput.MaxLength.HasValue)
                textBox.MaxLength = textInput.MaxLength.Value;

            textBox.Style = this.GetStyle($"Adaptive.Input.TextInput.{textInput.Style}");
            textBox.DataContext = textInput;
            inputControls.Add(textBox);
            return textBox;
        }

        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public UIElement Render(ChoiceInput choiceInput, List<FrameworkElement> inputControls)
        {
            var uiComboBox = new ComboBox();
            uiComboBox.Style = this.GetStyle("Adaptive.Input.ChoiceInput.ComboBox");
            uiComboBox.DataContext = choiceInput;

            var uiStackPanel = new StackPanel();
            uiStackPanel.DataContext = choiceInput;
            uiStackPanel.Orientation = Orientation.Vertical;
            uiStackPanel.Style = this.GetStyle("Adaptive.Input.ChoiceInput");

            foreach (var choice in choiceInput.Choices)
            {
                if (choiceInput.MultiSelect == true)
                {
                    var uiCheckbox = new CheckBox();
                    uiCheckbox.Content = choice.Display;
                    uiCheckbox.IsChecked = choice.IsSelected;
                    uiCheckbox.DataContext = choice;
                    uiCheckbox.Style = this.GetStyle("Adaptive.Input.ChoiceInput.CheckBox");
                    uiStackPanel.Children.Add(uiCheckbox);
                }
                else
                {
                    if (choiceInput.Style == ChoiceInputStyle.Compact)
                    {
                        var uiComboItem = new ComboBoxItem();
                        uiComboItem.Style = this.GetStyle("Adaptive.Input.ChoiceInput.ComboBoxItem");
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
                        uiRadio.GroupName = choiceInput.Id;
                        uiRadio.DataContext = choice;
                        uiRadio.Style = this.GetStyle("Adaptive.Input.ChoiceInput.Radio");
                        uiStackPanel.Children.Add(uiRadio);
                    }
                }
            }
            if (choiceInput.Style == ChoiceInputStyle.Compact)
            {
                inputControls.Add(uiComboBox);
                return uiComboBox;
            }
            else
            {
                inputControls.Add(uiStackPanel);
                return uiStackPanel;
            }
        }

        private dynamic _fillDataFromInputControls(dynamic data, List<FrameworkElement> inputControls)
        {
            foreach (var inputControl in inputControls)
            {
                if (inputControl.DataContext is TextInput)
                {
                    TextInput textInput = inputControl.DataContext as TextInput;
                    var value = GetValueFromInputControl(inputControl);
                    if (value != null)
                    {
                        data[textInput.Id] = JToken.FromObject(value);
                    }
                }
                else if (inputControl.DataContext is ChoiceInput)
                {
                    ChoiceInput choiceInput = (ChoiceInput)inputControl.DataContext;
                    var value = GetValueFromInputControl(inputControl);
                    if (value != null)
                    {
                        data[choiceInput.Id] = JToken.FromObject(value);
                    }
                }
            }
            return data;
        }

        public virtual object GetValueFromInputControl(FrameworkElement inputControl)
        {
            if (inputControl is TextBox)
            {
                return ((TextBox)inputControl).Text;
            }
            else if (inputControl is DatePicker)
            {
                return ((DatePicker)inputControl).Text;
            }
            else if (inputControl is PasswordBox)
            {
                return ((PasswordBox)inputControl).Password;
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
            else if (inputControl.DataContext is ChoiceInput)
            {
                ChoiceInput choiceInput = inputControl.DataContext as ChoiceInput;
                if (inputControl is StackPanel)
                {
                    var stack = inputControl as StackPanel;
                    if (choiceInput.MultiSelect == true)
                    {
                        List<string> values = new List<string>();
                        foreach (var child in stack.Children)
                        {
                            CheckBox checkBox = (CheckBox)child;
                            Choice choice = checkBox.DataContext as Choice;
                            if (checkBox.IsChecked == true)
                                values.Add(choice.Value);
                        }
                        return values;
                    }
                    else
                    {
                        foreach (var child in stack.Children)
                        {
                            RadioButton radioBox = (RadioButton)child;
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

        public virtual void ResetInputControl(FrameworkElement control)
        {
            if (control is TextBox)
            {
                TextInput input = control.DataContext as TextInput;
                ((TextBox)control).Text = input.Value;
            }
            else if (control is DatePicker)
            {
                TextInput input = control.DataContext as TextInput;
                ((DatePicker)control).Text = input.Value;
            }
            else if (control is PasswordBox)
            {
                TextInput input = control.DataContext as TextInput;
                ((PasswordBox)control).Password = input.Value;

            }
            else if (control is StackPanel && control.DataContext is ChoiceInput)
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
                ChoiceInput choiceInput = comboBox.DataContext as ChoiceInput;
                comboBox.SelectedIndex = 0;
            }
        }
    }
}