using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
#if Xamarin
using Xamarin.Forms;
using Xamarin.Forms.Xaml.Internals;
#elif WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using Xceed.Wpf.Toolkit;
#endif

namespace AdaptiveCards.Renderers
{

    public static class DictionaryHelper
    {
        public static T TryGetValue<T>(this IDictionary dictionary, string key)
        {
            if (dictionary == null)
                throw new ArgumentNullException(nameof(dictionary));

            if (dictionary.Contains(key))
            {
                return (T)dictionary[key];
            }

            return default(T);
        }

        public static T TryGetValue<T>(this IDictionary<string, object> dictionary, string key)
        {
            if (dictionary == null)
                throw new ArgumentNullException(nameof(dictionary));

            if (dictionary.ContainsKey(key))
            {
                return (T)dictionary[key];
            }

            return default(T);
        }
    }


    public class RenderContext
    {

        public RenderContext(Action<object, ActionEventArgs> actionCallback, Action<object, MissingInputEventArgs> missingDataCallback)
        {
            if (actionCallback != null)
                this.OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                this.OnMissingInput += (obj, args) => missingDataCallback(obj, args);
        }

        public Dictionary<string, MemoryStream> Images { get; private set; } = new Dictionary<string, MemoryStream>();


        /// <summary>
        /// Input Controls in scope for actions array
        /// </summary>
        public List<FrameworkElement> InputControls = new List<FrameworkElement>();

        /// <summary>
        /// Event fires when action is invoked
        /// </summary>
        public delegate void ActionEventHandler(object sender, ActionEventArgs e);
        public event ActionEventHandler OnAction;

        /// <summary>
        /// Event fires when missing input for submit/http actions
        /// </summary>
        public delegate void MissingInputEventHandler(object sender, MissingInputEventArgs e);
        public event MissingInputEventHandler OnMissingInput;

        public void Action(FrameworkElement ui, ActionEventArgs args)
        {
            this.OnAction?.Invoke(ui, args);
        }

        public void MissingInput(ActionBase sender, MissingInputEventArgs args)
        {
            this.OnMissingInput?.Invoke(sender, args);
        }

        public virtual dynamic MergeInputData(dynamic data)
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
                    bool hasValue = false;
                    if (value != null)
                    {
                        if (value is string && !String.IsNullOrEmpty((string)value))
                            hasValue = true;
                    }

                    if (hasValue)
                    {
                        data[input.Id] = JToken.FromObject(value);
                    }
                    else if (input.IsRequired)
                    {
                        throw new MissingInputException($"You are missing a required value.", input, inputControl);
                    }
                }

            }
            return data;
        }

        /// <summary>
        /// Override this to look at inputControl and return value for it
        /// </summary>
        /// <param name="inputControl"></param>
        /// <returns></returns>
        public virtual object GetValueFromInputControl(FrameworkElement inputControl)
        {
#if WPF
            // TODO: Enable
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
#endif
            return null;
        }

        public void ResetInput()
        {
            foreach (var control in this.InputControls)
            {
                ResetInputControl(control);
            }
        }

        /// <summary>
        /// Override to reset a control back to default state
        /// </summary>
        /// <param name="control"></param>
        public virtual void ResetInputControl(FrameworkElement control)
        {
#if WPF
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
#endif

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

    public class MissingInputEventArgs : EventArgs
    {
        public MissingInputEventArgs(Input input, FrameworkElement frameworkElement)
        {
            this.FrameworkElement = frameworkElement;
            this.Input = input;
        }

        public FrameworkElement FrameworkElement { get; private set; }

        public Input Input { get; private set; }
    }


    public class MissingInputException : Exception
    {
        public MissingInputException(string message, Input input, FrameworkElement frameworkElement)
            : base(message)
        {
            this.FrameworkElement = frameworkElement;
            this.Input = input;
        }

        public FrameworkElement FrameworkElement { get; set; }

        public Input Input { get; set; }
    }
}
