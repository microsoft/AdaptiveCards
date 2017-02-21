using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using Xceed.Wpf.Toolkit;
using Adaptive.Schema.Net;
using Newtonsoft.Json.Linq;
using Adaptive.Renderers;

namespace WpfVisualizer
{
    public class MyAdaptiveRenderer : AdaptiveXamlRenderer
    {
        public MyAdaptiveRenderer(ResourceDictionary resources) : base(resources)
        {

        }

        ///// <summary>
        ///// TextInput
        ///// </summary>
        ///// <param name="input"></param>
        ///// <returns></returns>
        //protected override UIElement Render(InputText textInput, List<FrameworkElement> inputControls)
        //{
        //    if (textInput.Style.HasValue)
        //    {
        //        switch (textInput.Style)
        //        {

        //            case TextInputStyle.Datetime:
        //                {
        //                    var dateTimePicker = new DateTimePicker();
        //                    dateTimePicker.TimePickerVisibility = Visibility.Visible;

        //                    DateTime value;
        //                    if (DateTime.TryParse(textInput.Value, out value))
        //                        dateTimePicker.Value = value;
        //                    DateTime minValue;
        //                    if (DateTime.TryParse(textInput.Min, out minValue))
        //                        dateTimePicker.Minimum = minValue;
        //                    DateTime maxValue;
        //                    if (DateTime.TryParse(textInput.Max, out maxValue))
        //                        dateTimePicker.Maximum = maxValue;
        //                    dateTimePicker.Watermark = textInput.Title;
        //                    dateTimePicker.Style = this.Resources["Adaptive.Input.TextInput.DateTime"] as Style;
        //                    dateTimePicker.DataContext = textInput;
        //                    inputControls.Add(dateTimePicker);
        //                    return dateTimePicker;
        //                }

        //            case TextInputStyle.Time:
        //                {
        //                    var timePicker = new TimePicker();
        //                    DateTime value;
        //                    if (DateTime.TryParse(textInput.Value, out value))
        //                        timePicker.Value = value;
        //                    TimeSpan minValue;
        //                    if (TimeSpan.TryParse(textInput.Min, out minValue))
        //                        timePicker.EndTime = minValue;
        //                    TimeSpan maxValue;
        //                    if (TimeSpan.TryParse(textInput.Max, out maxValue))
        //                        timePicker.EndTime = maxValue;
        //                    timePicker.Style = this.Resources["Adaptive.Input.TextInput.Time"] as Style;
        //                    timePicker.DataContext = textInput;
        //                    inputControls.Add(timePicker);
        //                    return timePicker;
        //                }

        //            case TextInputStyle.Number:
        //                {
        //                    IntegerUpDown numberPicker = new IntegerUpDown();
        //                    // numberPicker.ShowButtonSpinner = true;

        //                    float value;
        //                    if (float.TryParse(textInput.Value, out value))
        //                        numberPicker.Value = Convert.ToInt32(value);

        //                    float minValue;
        //                    if (float.TryParse(textInput.Min, out minValue))
        //                        numberPicker.Minimum = Convert.ToInt32(minValue);

        //                    float maxValue;
        //                    if (float.TryParse(textInput.Max, out maxValue))
        //                        numberPicker.Maximum = Convert.ToInt32(maxValue);

        //                    float step;
        //                    if (float.TryParse(textInput.Step, out step))
        //                        numberPicker.Increment = Convert.ToInt32(step);

        //                    numberPicker.Watermark = textInput.Title;
        //                    numberPicker.Style = this.Resources["Adaptive.Input.TextInput.Number"] as Style;
        //                    numberPicker.DataContext = textInput;
        //                    inputControls.Add(numberPicker);
        //                    return numberPicker;
        //                }

        //            case TextInputStyle.Tel:
        //                {
        //                    var telTextBox = new MaskedTextBox();
        //                    telTextBox.Text = textInput.Value;
        //                    telTextBox.Mask = "(000) 000 - 0000";
        //                    telTextBox.Style = this.Resources["Adaptive.Input.TextInput.Tel"] as Style;
        //                    telTextBox.DataContext = textInput;
        //                    inputControls.Add(telTextBox);
        //                    return telTextBox;
        //                }

        //            default:
        //                return base.Render(textInput, inputControls);
        //        }
        //    }
        //    var textBox = new WatermarkTextBox() { Text = textInput.Value };
        //    if (textInput.IsMultiline == true)
        //    {
        //        textBox.AcceptsReturn = true;
        //        textBox.TextWrapping = TextWrapping.Wrap;
        //        textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
        //    }
        //    if (textInput.MaxLength.HasValue)
        //        textBox.MaxLength = textInput.MaxLength.Value;

        //    textBox.Watermark = textInput.Title;
        //    textBox.Style = this.Resources[$"Adaptive.Input.TextInput.{textInput.Style}"] as Style ?? this.Resources[$"Adaptive.Input.TextInput"] as Style;
        //    textBox.DataContext = textInput;
        //    inputControls.Add(textBox);
        //    return textBox;
        //}


        //protected override object GetValueFromInputControl(FrameworkElement inputControl)
        //{
        //    if (inputControl is DateTimePicker)
        //    {
        //        return ((DateTimePicker)inputControl).Text;
        //    }
        //    else if (inputControl is WatermarkTextBox)
        //    {
        //        return ((WatermarkTextBox)inputControl).Text;
        //    }
        //    else if (inputControl is TimePicker)
        //    {
        //        return ((TimePicker)inputControl).Text;
        //    }
        //    else if (inputControl is IntegerUpDown)
        //    {
        //        return ((IntegerUpDown)inputControl).Text;
        //    }
        //    else if (inputControl is MaskedTextBox)
        //    {
        //        return ((MaskedTextBox)inputControl).Text;
        //    }
        //    return base.GetValueFromInputControl(inputControl);
        //}

        //protected override void ResetInputControl(FrameworkElement control)
        //{
        //    if (control is DateTimePicker)
        //    {
        //        InputText input = control.DataContext as InputText;
        //        ((DateTimePicker)control).Text = input.Value;
        //    }
        //    else if (control is TimePicker)
        //    {
        //        InputText input = control.DataContext as InputText;
        //        ((TimePicker)control).Text = input.Value;
        //    }
        //    else if (control is IntegerUpDown)
        //    {
        //        InputText input = control.DataContext as InputText;
        //        ((IntegerUpDown)control).Text = input.Value;
        //    }
        //    else if (control is MaskedTextBox)
        //    {
        //        InputText input = control.DataContext as InputText;
        //        ((MaskedTextBox)control).Text = input.Value;
        //    }
        //    else if (control is WatermarkTextBox)
        //    {
        //        InputText input = control.DataContext as InputText;
        //        ((WatermarkTextBox)control).Text = input.Value;
        //    }
        //    else
        //        base.ResetInputControl(control);
        //}

    }
}