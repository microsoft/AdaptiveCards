using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards
{
    public static class FrameworkElementExtensions
    {
        public static object GetValue(this FrameworkElement inputControl)
        {
            if (inputControl is WatermarkTextBox wtb)
            {
                return wtb.Text;
            }

            if (inputControl is TextBox tb)
            {
                return tb.Text;
            }

            if (inputControl is DatePicker dp)
            {
                return dp.Text;
            }

            if (inputControl is CheckBox toggleSwitch)
            {
                if (toggleSwitch.IsChecked == true)
                    return ((InputToggle)toggleSwitch.DataContext).ValueOn;
                else
                    return ((InputToggle)toggleSwitch.DataContext).ValueOff;
            }

            if (inputControl is PasswordBox pb)
            {
                return pb.Password;
            }

            if (inputControl is TimePicker tp)
            {
                return tp.Text;
            }

            if (inputControl is IntegerUpDown iud)
            {
                return iud.Text;
            }

            if (inputControl is ComboBox)
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

            if (inputControl.DataContext is InputChoiceSet choiceInput)
            {
                if (inputControl is ListBox choices)
                {
                    if (choiceInput.IsMultiSelect == true)
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

        public static void ResetValue(this FrameworkElement control)
        {
            if (control is TextBox tb)
            {
                var input = control.DataContext as InputText;
                tb.Text = input.Value;
                return;
            }

            if (control is DatePicker dp)
            {
                var input = control.DataContext as InputText;
                dp.Text = input.Value;
                return;
            }

            if (control is TimePicker tp)
            {
                var input = control.DataContext as InputText;
                tp.Text = input.Value;
                return;
            }

            if (control is IntegerUpDown iud)
            {
                var input = control.DataContext as InputText;
                iud.Text = input.Value;
                return;
            }

            if (control is WatermarkTextBox wtb)
            {
                var input = control.DataContext as InputText;
                wtb.Text = input.Value;
            }

            if (control is PasswordBox pb)
            {
                var input = control.DataContext as InputText;
                pb.Password = input.Value;
            }

            if (control is StackPanel stack && control.DataContext is InputChoiceSet)
            {
                foreach (var child in stack.Children)
                {
                    if (child is CheckBox checkBox)
                    {
                        var choice = checkBox.DataContext as Choice;
                        checkBox.IsChecked = choice.IsSelected == true;
                    }
                    else if (child is RadioButton radioBox)
                    {;
                        var choice = radioBox.DataContext as Choice;
                        radioBox.IsChecked = choice.IsSelected == true;
                    }
                }
                return;
            }

            if (control is ComboBox comboBox)
            {
                var choiceInput = comboBox.DataContext as InputChoiceSet;
                comboBox.SelectedIndex = 0;
                return;
            }
        }
    }
}
