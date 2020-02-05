using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Xamarin.Forms;

namespace AdaptiveCards
{
    public static class FrameworkElementExtensions
    {
        public static object GetValue(this View inputControl)
        {
            if (inputControl is TextBox tb)
            {
                return tb.Text;
            }

            if (inputControl is DatePicker dp)
            {
                return dp.Date;
            }

            //if (inputControl is CheckBox cb)
            //{
            //    var toggleSwitch = (CheckBox)inputControl;
            //    if (toggleSwitch.IsChecked == true)
            //        return ((InputToggle)toggleSwitch.BindingContext).ValueOn;
            //    else
            //        return ((InputToggle)toggleSwitch.BindingContext).ValueOff;
            //}


            if (inputControl is TimePicker tp)
            {
                return tp.Time;
            }

            //if (inputControl is IntegerUpDown)
            //{
            //    return ((IntegerUpDown)inputControl).Text;
            //}

            if (inputControl is Picker p)
            {
                return p.SelectedItem;
            }

            //if (inputControl.BindingContext is InputChoiceSet)
            //{
            //    InputChoiceSet choiceInput = inputControl.BindingContext as InputChoiceSet;
            //    if (inputControl is ListBox)
            //    {
            //        var choices = inputControl as ListBox;
            //        if (choiceInput.IsMultiSelect == true)
            //        {
            //            List<string> values = new List<string>();
            //            foreach (var item in choices.Items)
            //            {
            //                CheckBox checkBox = (CheckBox)item;
            //                Choice choice = checkBox.BindingContext as Choice;
            //                if (checkBox.IsChecked == true)
            //                    values.Add(choice.Value);
            //            }
            //            return values;
            //        }
            //        else
            //        {
            //            foreach (var item in choices.Items)
            //            {
            //                RadioButton radioBox = (RadioButton)item;
            //                Choice choice = radioBox.BindingContext as Choice;
            //                if (radioBox.IsChecked == true)
            //                    return choice.Value;
            //            }
            //            return null;
            //        }
            //    }
            //}
            Debug.Write($"Unknown control {inputControl.GetType().Name}");
            return null;

        }

        public static void ResetValue(this View control)
        {
            if (control is TextBox tb)
            {
                var input = control.BindingContext as AdaptiveTextInput;
                tb.Text = input.Value;
                return;
            }

            if (control is DatePicker dp)
            {
                var input = control.BindingContext as AdaptiveTextInput;
                DateTime.TryParse(input.Value, out var date);
                dp.Date = date;
                return;
            }

            if (control is TimePicker tp)
            {
                var input = control.BindingContext as AdaptiveTextInput;
                TimeSpan.TryParse(input.Value, out var time);
                tp.Time = time;
                return;
            }

            //if (control is IntegerUpDown iud)
            //{
            //    var input = control.BindingContext as InputText;
            //    iud.Text = input.Value;
            //    return;
            //}

            //if (control is WatermarkTextBox wtb)
            //{
            //    var input = control.BindingContext as InputText;
            //    wtb.Text = input.Value;
            //}

          
            //if (control is StackPanel stack && control.BindingContext is InputChoiceSet)
            //{
            //    foreach (var child in stack.Children)
            //    {
            //        if (child is CheckBox checkBox)
            //        {
            //            var choice = checkBox.BindingContext as Choice;
            //            checkBox.IsChecked = choice.IsSelected == true;
            //        }
            //        else if (child is RadioButton radioBox)
            //        {
            //            ;
            //            var choice = radioBox.BindingContext as Choice;
            //            radioBox.IsChecked = choice.IsSelected == true;
            //        }
            //    }
            //    return;
            //}

            if (control is Picker comboBox)
            {
                var choiceInput = comboBox.BindingContext as AdaptiveChoiceSetInput;
                comboBox.SelectedIndex = 0;
                return;
            }
        }
    }
}
