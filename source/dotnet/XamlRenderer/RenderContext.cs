using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using Newtonsoft.Json.Linq;
using Xceed.Wpf.Toolkit;

namespace Adaptive
{

    public class RenderContext
    {
        public RenderContext(ResourceDictionary resources)
        {
            this.Resources = resources;
        }

        public RenderContext NewActionContext()
        {
            return new RenderContext(this.Resources)
            {
                ShowInput = this.ShowInput,
                ShowAction = this.ShowAction,
                OnAction = this.OnAction
            };
        }

        public bool ShowInput = true;

        public bool ShowAction = true;

        public List<FrameworkElement> InputControls = new List<FrameworkElement>();

        public ResourceDictionary Resources;

        public delegate void ActionEventHandler(object sender, ActionEventArgs e);

        /// <summary>
        /// Event fires when action is invoked
        /// </summary>
        public event ActionEventHandler OnAction;

        public void Invoke(FrameworkElement ui, ActionEventArgs args)
        {
            this.OnAction?.Invoke(ui, args);
        }

        public virtual Style GetStyle(string styleName)
        {
            if (!styleName.Contains(".Tap"))
            {
                if (styleName.Contains(".Input") && !this.ShowInput)
                {
                    return this.Resources["Hidden"] as Style;
                }

                if (styleName.Contains(".Action") && !this.ShowAction)
                {
                    return this.Resources["Hidden"] as Style;
                }
            }

            while (!String.IsNullOrEmpty(styleName))
            {
                Style style = this.Resources[styleName] as Style;
                if (style != null)
                    return style;
                var iPos = styleName.LastIndexOf('.');
                if (iPos <= 0)
                    break;
                styleName = styleName.Substring(0, iPos);
            }
            return null;
        }


        public dynamic MergeInputData(dynamic data)
        {
            foreach (var inputControl in this.InputControls)
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
            else if (inputControl is CheckBox)
            {
                var toggleSwitch = (CheckBox)inputControl;
                if (toggleSwitch.IsChecked == true)
                    return ((InputToggle)toggleSwitch.DataContext).ValueOn;
                else
                    return ((InputToggle)toggleSwitch.DataContext).ValueOff;
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

        public void ResetInput()
        {
            foreach (var control in this.InputControls)
            {
                ResetInputControl(control);
            }
        }

        protected void ResetInputControl(FrameworkElement control)
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
            //else if (control is HorizontalToggleSwitch)
            //{
            //    InputToggle inputToggle = control.DataContext as InputToggle;
            //    ((HorizontalToggleSwitch)control).IsChecked = inputToggle.Value == inputToggle.ValueOn;
            //}
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


    public class ActionEventArgs : EventArgs
    {
        public ActionEventArgs()
        { }

        /// <summary>
        /// The action that fired
        /// </summary>
        public ActionBase Action { get; set; }

        /// <summary>
        /// Data for Input controls (if appropriate)
        /// </summary>
        public object Data { get; set; }
    }

}
