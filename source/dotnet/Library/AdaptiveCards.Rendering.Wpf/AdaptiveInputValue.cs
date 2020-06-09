// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.IO;
using System.Security.Cryptography;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering.Wpf
{
    public abstract class AdaptiveInputValue
    {
        public AdaptiveInputValue(AdaptiveInput input, UIElement renderedInput)
        {
            InputElement = input;
            RenderedInputElement = renderedInput;
        }

        public abstract string GetValue();

        public abstract bool Validate();

        public abstract void SetFocus();

        public AdaptiveInput InputElement { get; set; }

        // This may not be required
        public UIElement RenderedInputElement { get; set; }
    }

    /// <summary>
    /// Abstract class that implements the Validate behaviour for isRequired in almost all inputValues (except for Input.Toggle)
    /// </summary>
    public abstract class AdaptiveInputValueRequiredValidation : AdaptiveInputValue
    {
        public AdaptiveInputValueRequiredValidation(AdaptiveInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override bool Validate()
        {
            bool isValid = true;

            if (InputElement.IsRequired)
            {
                isValid = String.IsNullOrEmpty(GetValue());
            }

            return isValid;
        }
    }

    /// <summary>
    /// Intermediate class, as most of the elements in the vanilla wpf (no xceed) renderers use a textbox,
    /// this class was created to avoid all inputValues to implement the same GetValue and Focus method
    /// </summary>
    public class AdaptiveTextBoxInputValue : AdaptiveInputValueRequiredValidation
    {
        public AdaptiveTextBoxInputValue(AdaptiveInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            return (RenderedInputElement as TextBox).Text;
        }

        public override void SetFocus()
        {
            RenderedInputElement.Focus();
        }
    }

    public class AdaptiveTextInputValue : AdaptiveTextBoxInputValue
    {
        public AdaptiveTextInputValue(AdaptiveTextInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override bool Validate()
        {
            bool isValid = base.Validate();

            AdaptiveTextInput textInput = InputElement as AdaptiveTextInput;

            if (!String.IsNullOrEmpty(textInput.Regex))
            {
                isValid = isValid && Regex.IsMatch(GetValue(), textInput.Regex);
            }

            if (textInput.MaxLength != 0)
            {
                isValid = isValid && (GetValue().Length <= textInput.MaxLength);
            }

            return isValid;
        }
    }

    public class AdaptiveNumberInputValue : AdaptiveTextBoxInputValue
    {
        public AdaptiveNumberInputValue(AdaptiveNumberInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override bool Validate()
        {
            bool isValid = base.Validate();

            double inputValue = 0.0;
            isValid = isValid && Double.TryParse(GetValue(), out inputValue);

            if (isValid)
            {
                AdaptiveNumberInput numberInput = InputElement as AdaptiveNumberInput;

                bool isMinValid = true, isMaxValid = true;
                if (!Double.IsNaN(numberInput.Min))
                {
                    isMinValid = (inputValue >= numberInput.Min);
                }

                if (!Double.IsNaN(numberInput.Max))
                {
                    isMaxValid = (inputValue <= numberInput.Max);
                }

                isValid = isValid && isMinValid && isMaxValid;
            }

            return isValid;
        }
    }

    public class AdaptiveDateInputValue : AdaptiveTextBoxInputValue
    {
        public AdaptiveDateInputValue(AdaptiveDateInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            return ToIso8601Date(base.GetValue());
        }

        public override bool Validate()
        {
            bool isValid = base.Validate();

            // Check if our input is valid
            DateTime inputValue;
            if (DateTime.TryParse(GetValue(), out inputValue))
            {
                AdaptiveDateInput dateInput = InputElement as AdaptiveDateInput;
                DateTime minDate, maxDate;

                if (!String.IsNullOrEmpty(dateInput.Min))
                {
                    // if min is a valid date, compare against it, otherwise ignore
                    if (DateTime.TryParse(dateInput.Min, out minDate))
                    {
                        isValid = isValid && (inputValue >= minDate);
                    }
                }

                if (!String.IsNullOrEmpty(dateInput.Max))
                {
                    // if max is a valid date, compare against it, otherwise ignore
                    if (DateTime.TryParse(dateInput.Max, out maxDate))
                    {
                        isValid = isValid && (inputValue >= maxDate);
                    }
                }
            }
            else
            {
                isValid = false;
            }

            return isValid;
        }

        protected string ToIso8601Date(string text)
        {
            if (string.IsNullOrEmpty(text))
            {
                return string.Empty;
            }

            DateTime dateTime;
            if (DateTime.TryParse(text, null, System.Globalization.DateTimeStyles.RoundtripKind, out dateTime))
            {
                return dateTime.ToString("yyyy-MM-dd");
            }

            return text;
        }
    }

    public class AdaptiveTimeInputValue : AdaptiveTextBoxInputValue
    {
        public AdaptiveTimeInputValue(AdaptiveTimeInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            return ToIso8601Time(base.GetValue());
        }

        public override bool Validate()
        {
            bool isValid = base.Validate();

            // Check if our input is valid
            TimeSpan inputValue;
            if (TimeSpan.TryParse(GetValue(), out inputValue))
            {
                AdaptiveTimeInput timeInput = InputElement as AdaptiveTimeInput;
                TimeSpan minTime, maxTime;

                if (!String.IsNullOrEmpty(timeInput.Min))
                {
                    // if min is a valid date, compare against it, otherwise ignore
                    if (TimeSpan.TryParse(timeInput.Min, out minTime))
                    {
                        isValid = isValid && (inputValue >= minTime);
                    }
                }

                if (!String.IsNullOrEmpty(timeInput.Max))
                {
                    // if max is a valid date, compare against it, otherwise ignore
                    if (TimeSpan.TryParse(timeInput.Max, out maxTime))
                    {
                        isValid = isValid && (inputValue >= maxTime);
                    }
                }
            }
            else
            {
                isValid = false;
            }

            return isValid;
        }

        protected string ToIso8601Time(string text)
        {
            if (string.IsNullOrEmpty(text))
            {
                return string.Empty;
            }

            DateTime dateTime;
            if (DateTime.TryParse(text, null, System.Globalization.DateTimeStyles.RoundtripKind, out dateTime))
            {
                return dateTime.ToString("HH:mm");
            }

            return text;
        }
    }

    public class AdaptiveChoiceSetInputValue : AdaptiveInputValueRequiredValidation
    {
        public AdaptiveChoiceSetInputValue(AdaptiveChoiceSetInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            AdaptiveChoiceSetInput input = InputElement as AdaptiveChoiceSetInput;

            if (input.IsMultiSelect)
            {
                Panel uiChoices = RenderedInputElement as Panel;

                string values = string.Empty;
                foreach (var item in uiChoices.Children)
                {
                    CheckBox checkBox = (CheckBox)item;
                    AdaptiveChoice adaptiveChoice = checkBox.DataContext as AdaptiveChoice;
                    if (checkBox.IsChecked == true)
                        values += (values == string.Empty ? "" : ",") + adaptiveChoice.Value;
                }
                return values;
            }
            else
            {
                ComboBox uiComboBox = RenderedInputElement as ComboBox;

                if (input.Style == AdaptiveChoiceInputStyle.Compact)
                {
                    ComboBoxItem item = uiComboBox.SelectedItem as ComboBoxItem;
                    if (item != null)
                    {
                        AdaptiveChoice adaptiveChoice = item.DataContext as AdaptiveChoice;
                        return adaptiveChoice.Value;
                    }
                    return null;
                }
                else
                {
                    Panel uiChoices = RenderedInputElement as Panel;

                    foreach (var item in uiChoices.Children)
                    {
                        RadioButton radioBox = (RadioButton)item;
                        AdaptiveChoice adaptiveChoice = radioBox.DataContext as AdaptiveChoice;
                        if (radioBox.IsChecked == true)
                            return adaptiveChoice.Value;
                    }
                    return null;
                }
            }
        }

        public override void SetFocus()
        {
            throw new NotImplementedException();
        }
    }

    public class AdaptiveToggleInputValue : AdaptiveInputValue
    {
        public AdaptiveToggleInputValue(AdaptiveToggleInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            CheckBox uiToggle = RenderedInputElement as CheckBox;
            AdaptiveToggleInput toggleInput = InputElement as AdaptiveToggleInput;

            return (uiToggle.GetState() == true ? toggleInput.ValueOn ?? "true" : toggleInput.ValueOff ?? "false");
        }

        public override void SetFocus()
        {
            RenderedInputElement.Focus();
        }

        public override bool Validate()
        {
            bool isValid = true;

            if (InputElement.IsRequired)
            {
                AdaptiveToggleInput toggleInput = InputElement as AdaptiveToggleInput;
                isValid = (GetValue() == toggleInput.ValueOn);
            }

            return isValid;
        }
    }
}
