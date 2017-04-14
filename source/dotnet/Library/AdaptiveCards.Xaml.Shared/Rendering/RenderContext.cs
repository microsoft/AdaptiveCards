using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
#if XAMARIN
using Xamarin.Forms;
using Xamarin.Forms.Xaml.Internals;
#elif WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Xceed.Wpf.Toolkit;
#endif

namespace AdaptiveCards.Rendering
{
    public class RenderContext
    {
        private Func<string, MemoryStream> _imageResolver = null;

        public RenderContext(Action<object, ActionEventArgs> actionCallback,
            Action<object, MissingInputEventArgs> missingDataCallback,
            Func<string, MemoryStream> imageResolver = null)
        {
            if (actionCallback != null)
                this.OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                this.OnMissingInput += (obj, args) => missingDataCallback(obj, args);

            this._imageResolver = imageResolver;
        }

        public HostOptions Options { get; set; } = new HostOptions();

        public Dictionary<string, Func<TypedElement, RenderContext, FrameworkElement>> ElementRenderers = new Dictionary<string, Func<TypedElement, RenderContext, FrameworkElement>>();

        public FrameworkElement Render(TypedElement element)
        {
            if (ElementRenderers.TryGetValue(element.Type, out Func<TypedElement, RenderContext, FrameworkElement> renderer))
            {
                return renderer(element, this);
            }
            return null;
        }

#if WPF
        public BitmapImage ResolveImageSource(string url)
        {
            BitmapImage source = null;
            if (this._imageResolver != null)
            {
                // off screen rendering can pass already loaded image to us so we can render immediately
                var stream = this._imageResolver(url);
                if (stream != null)
                {
                    source = new BitmapImage();
                    source.BeginInit();
                    source.StreamSource = stream;
                    source.EndInit();
                }
            }
            return source ?? new BitmapImage(new Uri(url));
        }
#endif

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
#if WPF
        private static Dictionary<string, SolidColorBrush> colors = new Dictionary<string, SolidColorBrush>();

        public SolidColorBrush GetColorBrush(string color)
        {
            lock (colors)
            {
                if (colors.TryGetValue(color, out var brush))
                    return brush;
                brush = new SolidColorBrush((Color)ColorConverter.ConvertFromString(color));
                colors[color] = brush;
                return brush;
            }
        }
#elif XAMARIN
        // TODO
        public object GetColorBrush(string color)
        {
            return null;
        }
#endif

        public ResourceDictionary Resources { get; set; }


        public virtual Style GetStyle(string styleName)
        {
            while (!String.IsNullOrEmpty(styleName))
            {
                Style style = this.Resources.TryGetValue<Style>(styleName);
                if (style != null)
                    return style;
                var iPos = styleName.LastIndexOf('.');
                if (iPos <= 0)
                    break;
                styleName = styleName.Substring(0, iPos);
            }

            // Debug.WriteLine($"Unable to find Style {styleName} from the supplied ResourceDictionary");
            return null;
        }


        public virtual dynamic MergeInputData(dynamic data)
        {
            foreach (var inputControl in this.InputControls)
            {
                if (inputControl.DataContext is ChoiceSet)
                {
                    ChoiceSet choiceInput = (ChoiceSet)inputControl.DataContext;
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
                    return ((ToggleInput)toggleSwitch.DataContext).ValueOn;
                else
                    return ((ToggleInput)toggleSwitch.DataContext).ValueOff;
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
            else if (inputControl.DataContext is ChoiceSet)
            {
                ChoiceSet choiceInput = inputControl.DataContext as ChoiceSet;
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
            // TODO: Xamarin inputs
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
                TextInput input = control.DataContext as TextInput;
                ((TextBox)control).Text = input.Value;
            }
            else if (control is DatePicker)
            {
                TextInput input = control.DataContext as TextInput;
                ((DatePicker)control).Text = input.Value;
            }
            else if (control is TimePicker)
            {
                TextInput input = control.DataContext as TextInput;
                ((TimePicker)control).Text = input.Value;
            }
            else if (control is IntegerUpDown)
            {
                TextInput input = control.DataContext as TextInput;
                ((IntegerUpDown)control).Text = input.Value;
            }
            else if (control is WatermarkTextBox)
            {
                TextInput input = control.DataContext as TextInput;
                ((WatermarkTextBox)control).Text = input.Value;
            }
            else if (control is PasswordBox)
            {
                TextInput input = control.DataContext as TextInput;
                ((PasswordBox)control).Password = input.Value;
            }
            else if (control is StackPanel && control.DataContext is ChoiceSet)
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
                ChoiceSet choiceInput = comboBox.DataContext as ChoiceSet;
                comboBox.SelectedIndex = 0;
            }
#endif

        }

    }


    public class ActionEventArgs : EventArgs
    {
        public ActionEventArgs()
        {
        }

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
