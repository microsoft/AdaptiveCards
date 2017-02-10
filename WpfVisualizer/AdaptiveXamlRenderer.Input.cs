using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Xceed.Wpf.Toolkit;
using AC = Adaptive.Schema.Net;

namespace WpfVisualizer
{
    public partial class AdaptiveXamlRenderer
    {

        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public UIElement Render(AC.TextInput textInput, List<Control> inputControls)
        {
            if (textInput.Style.HasValue)
            {
                switch (textInput.Style)
                {
                    case AC.TextInputStyle.Week:
                    case AC.TextInputStyle.Date:
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
                            datePicker.Style = this.resources["Adaptive.Input.TextInput.Date"] as Style;
                            datePicker.Tag = textInput;
                            inputControls.Add(datePicker);
                            return datePicker;
                        }

                    case AC.TextInputStyle.Datetime:
                        {
                            var dateTimePicker = new DateTimePicker();
                            dateTimePicker.TimePickerVisibility = Visibility.Visible;

                            DateTime value;
                            if (DateTime.TryParse(textInput.Value, out value))
                                dateTimePicker.Value = value;
                            DateTime minValue;
                            if (DateTime.TryParse(textInput.Min, out minValue))
                                dateTimePicker.Minimum = minValue;
                            DateTime maxValue;
                            if (DateTime.TryParse(textInput.Max, out maxValue))
                                dateTimePicker.Maximum = maxValue;
                            dateTimePicker.Watermark = textInput.Placeholder;
                            dateTimePicker.Style = this.resources["Adaptive.Input.TextInput.DateTime"] as Style;
                            dateTimePicker.Tag = textInput;
                            inputControls.Add(dateTimePicker);
                            return dateTimePicker;
                        }

                    case AC.TextInputStyle.Time:
                        {
                            var timePicker = new TimePicker();
                            DateTime value;
                            if (DateTime.TryParse(textInput.Value, out value))
                                timePicker.Value = value;
                            TimeSpan minValue;
                            if (TimeSpan.TryParse(textInput.Min, out minValue))
                                timePicker.EndTime = minValue;
                            TimeSpan maxValue;
                            if (TimeSpan.TryParse(textInput.Max, out maxValue))
                                timePicker.EndTime = maxValue;
                            timePicker.Style = this.resources["Adaptive.Input.TextInput.Time"] as Style;
                            timePicker.Tag = textInput;
                            inputControls.Add(timePicker);
                            return timePicker;
                        }

                    case AC.TextInputStyle.Number:
                        {
                            IntegerUpDown numberPicker = new IntegerUpDown();
                            // numberPicker.ShowButtonSpinner = true;

                            float value;
                            if (float.TryParse(textInput.Value, out value))
                                numberPicker.Value = Convert.ToInt32(value);

                            float minValue;
                            if (float.TryParse(textInput.Min, out minValue))
                                numberPicker.Minimum = Convert.ToInt32(minValue);

                            float maxValue;
                            if (float.TryParse(textInput.Max, out maxValue))
                                numberPicker.Maximum = Convert.ToInt32(maxValue);

                            float step;
                            if (float.TryParse(textInput.Step, out step))
                                numberPicker.Increment = Convert.ToInt32(step);

                            numberPicker.Watermark = textInput.Placeholder;
                            numberPicker.Style = this.resources["Adaptive.Input.TextInput.Number"] as Style;
                            numberPicker.Tag = textInput;
                            inputControls.Add(numberPicker);
                            return numberPicker;
                        }


                    case AC.TextInputStyle.Password:
                        {
                            PasswordBox passwordBox = new PasswordBox() { Password = textInput.Value };

                            if (textInput.MaxLength.HasValue)
                                passwordBox.MaxLength = textInput.MaxLength.Value;

                            passwordBox.Style = this.resources["Adaptive.Input.TextInput.Password"] as Style;
                            passwordBox.Tag = textInput;
                            inputControls.Add(passwordBox);
                            return passwordBox;
                        }

                    case AC.TextInputStyle.Range:
                        {
                            var rangeGrid = new Grid();
                            rangeGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                            rangeGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                            rangeGrid.Style = this.resources["Adapative.Input.TextInput.Range"] as Style;

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
                            tb.Style = this.resources["Adaptive.Input.TextInput.Range.TextBox"] as Style;
                            tb.Tag = textInput;
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

                    case AC.TextInputStyle.Tel:
                        {
                            var telTextBox = new MaskedTextBox();
                            telTextBox.Text = textInput.Value;
                            telTextBox.Mask = "(000) 000 - 0000";
                            telTextBox.Style = this.resources["Adaptive.Input.TextInput.Tel"] as Style;
                            telTextBox.Tag = textInput;
                            inputControls.Add(telTextBox);
                            return telTextBox;
                        }

                    case AC.TextInputStyle.Email:
                    case AC.TextInputStyle.Month:
                    default:
                        break;
                }
            }

            var textBox = new WatermarkTextBox() { Text = textInput.Value };
            if (textInput.IsMultiline == true)
            {
                textBox.AcceptsReturn = true;
                textBox.TextWrapping = TextWrapping.Wrap;
                textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
            }
            if (textInput.MaxLength.HasValue)
                textBox.MaxLength = textInput.MaxLength.Value;

            textBox.Watermark = textInput.Placeholder;
            textBox.Style = this.resources[$"Adaptive.Input.TextInput.{textInput.Style}"] as Style ?? this.resources[$"Adaptive.Input.TextInput"] as Style;
            textBox.Tag = textInput;
            inputControls.Add(textBox);
            return textBox;
        }

        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public UIElement Render(AC.ChoiceInput choiceInput, List<Control> inputControls)
        {
            var uiComboBox = new ComboBox();
            uiComboBox.Style = resources["Adaptive.Input.ChoiceInput.ComboBox"] as Style;
            uiComboBox.Tag = choiceInput;

            var uiStackPanel = new StackPanel();
            uiStackPanel.Tag = choiceInput;
            uiStackPanel.Orientation = Orientation.Vertical;
            uiStackPanel.Style = resources["Adaptive.Input.ChoiceInput"] as Style;

            foreach (var choice in choiceInput.Choices)
            {
                if (choiceInput.MultiSelect == true)
                {
                    var uiCheckbox = new CheckBox();
                    uiCheckbox.Content = choice.Display;
                    uiCheckbox.IsChecked = choice.IsSelected;
                    uiCheckbox.Tag = new Tuple<AC.ChoiceInput, AC.Choice>(choiceInput, choice);
                    uiCheckbox.Style = resources["Adaptive.Input.ChoiceInput.CheckBox"] as Style;
                    inputControls.Add(uiCheckbox);
                    uiStackPanel.Children.Add(uiCheckbox);
                }
                else
                {
                    if (choiceInput.Style == AC.ChoiceInputStyle.Compact)
                    {
                        var uiComboItem = new ComboBoxItem();
                        uiComboItem.Style = resources["Adaptive.Input.ChoiceInput.ComboBoxItem"] as Style;
                        uiComboItem.Content = choice.Display;
                        uiComboItem.Tag = new Tuple<AC.ChoiceInput, AC.Choice>(choiceInput, choice);
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
                        uiRadio.Tag = new Tuple<AC.ChoiceInput, AC.Choice>(choiceInput, choice);
                        uiRadio.Style = resources["Adaptive.Input.ChoiceInput.Radio"] as Style;
                        inputControls.Add(uiRadio);
                        uiStackPanel.Children.Add(uiRadio);
                    }
                }
            }
            if (choiceInput.Style == AC.ChoiceInputStyle.Compact)
            {
                inputControls.Add(uiComboBox);
                return uiComboBox;
            }
            return uiStackPanel;
        }
    }
}