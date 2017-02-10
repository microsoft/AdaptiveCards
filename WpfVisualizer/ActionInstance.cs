using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using Adaptive.Schema.Net;
using Newtonsoft.Json.Linq;
using Xceed.Wpf.Toolkit;

namespace WpfVisualizer
{
    public class ActionInstance
    {
        public ActionInstance()
        {

        }

        public ActionBase Action { get; set; }

        public List<Control> Inputs { get; set; }

        public dynamic GetDataFromControls()
        {
            dynamic data = null;
            if (Action is SubmitAction)
                data = ((SubmitAction)Action).Data;

            if (data != null)
                data = data.DeepClone();
            else
                data = new JObject();

            foreach (var control in Inputs)
            {
                if (control is TextBox)
                {
                    TextInput input = control.Tag as TextInput;
                    data[input.Id] = ((TextBox)control).Text;
                }
                else if (control is DatePicker)
                {
                    TextInput input = control.Tag as TextInput;
                    data[input.Id] = ((DatePicker)control).Text; 
                }
                else if (control is DateTimePicker)
                {
                    TextInput input = control.Tag as TextInput;
                    data[input.Id] = ((DateTimePicker)control).Text;
                }
                else if (control is TimePicker)
                {
                    TextInput input = control.Tag as TextInput;
                    data[input.Id] = ((TimePicker)control).Text;
                }
                else if (control is IntegerUpDown)
                {
                    TextInput input = control.Tag as TextInput;
                    data[input.Id] = ((IntegerUpDown)control).Text;
                }
                else if (control is PasswordBox)
                {
                    TextInput input = control.Tag as TextInput;
                    data[input.Id] = ((PasswordBox)control).Password;
                }
                else if (control is MaskedTextBox)
                {
                    TextInput input = control.Tag as TextInput;
                    data[input.Id] = ((MaskedTextBox)control).Text;
                }
                else if (control is CheckBox)
                {
                    CheckBox checkBox = (CheckBox)control;
                    var tuple = control.Tag as Tuple<ChoiceInput, Choice>;
                    if (data[tuple.Item1.Id] == null)
                        data[tuple.Item1.Id] = new List<String>();
                    if (checkBox.IsChecked == true)
                        data[tuple.Item1.Id].Add(tuple.Item2.Value);
                }
                else if (control is RadioButton)
                {
                    RadioButton radioBox = (RadioButton)control;
                    var tuple = control.Tag as Tuple<ChoiceInput, Choice>;
                    if (radioBox.IsChecked == true)
                        data[tuple.Item1.Id] = tuple.Item2.Value;
                }
                else if (control is ComboBox)
                {
                    //ComboBox comboBox = (ComboBox)control;
                    //var tuple = control.Tag as Tuple<ChoiceInput, Choice>;
                    //if (comboBox.IsChecked == true)
                    //    data[tuple.Item1.Id] = tuple.Item2.Value;
                }
            }
            return data;
        }

        public void Reset()
        {
            Reset(this.Inputs);
        }

        public static void Reset(List<Control> inputControls)
        {
            foreach (var control in inputControls)
            {
                if (control is TextBox)
                {
                    TextInput input = control.Tag as TextInput;
                    ((TextBox)control).Text = input.Value;
                }
                else if (control is DatePicker)
                {
                    TextInput input = control.Tag as TextInput;
                    ((DatePicker)control).Text = input.Value;
                }
                else if (control is DateTimePicker)
                {
                    TextInput input = control.Tag as TextInput;
                    ((DateTimePicker)control).Text = input.Value;
                }
                else if (control is TimePicker)
                {
                    TextInput input = control.Tag as TextInput;
                    ((TimePicker)control).Text = input.Value;
                }
                else if (control is IntegerUpDown)
                {
                    TextInput input = control.Tag as TextInput;
                    ((IntegerUpDown)control).Text = input.Value;
                }
                else if (control is PasswordBox)
                {
                    TextInput input = control.Tag as TextInput;
                    ((PasswordBox)control).Password = input.Value;
                }
                else if (control is MaskedTextBox)
                {
                    TextInput input = control.Tag as TextInput;
                    ((MaskedTextBox)control).Text = input.Value;
                }
                else if (control is CheckBox)
                {
                    CheckBox checkBox = (CheckBox)control;
                    var tuple = control.Tag as Tuple<ChoiceInput, Choice>;
                    checkBox.IsChecked = tuple.Item2.IsSelected == true;
                }
                else if (control is RadioButton)
                {
                    RadioButton radioBox = (RadioButton)control;
                    var tuple = control.Tag as Tuple<ChoiceInput, Choice>;
                    radioBox.IsChecked = tuple.Item2.IsSelected == true;
                }
                else if (control is ComboBox)
                {
                    //ComboBox comboBox = (ComboBox)control;
                    //var tuple = control.Tag as Tuple<ChoiceInput, Choice>;
                    //if (comboBox.IsChecked == true)
                    //    data[tuple.Item1.Id] = tuple.Item2.Value;
                }
            }
        }
    }
}
