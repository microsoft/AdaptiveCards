// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;
using System.Windows.Controls;
using System.Text.RegularExpressions;
using Xceed.Wpf.Toolkit;

namespace AdaptiveCards.Rendering.Wpf
{

    public class AdaptiveXceedTextInputValue : AdaptiveTextInputValue
    {
        public AdaptiveXceedTextInputValue(AdaptiveTextInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            return (RenderedInputElement as WatermarkTextBox).Text;
        }
    }

    public class AdaptiveXceedNumberInputValue : AdaptiveNumberInputValue
    {
        public AdaptiveXceedNumberInputValue(AdaptiveNumberInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            return (RenderedInputElement as DoubleUpDown).Value?.ToString();
        }
    }

    public class AdaptiveXceedDateInputValue : AdaptiveDateInputValue
    {
        public AdaptiveXceedDateInputValue(AdaptiveDateInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            return ToIso8601Date((RenderedInputElement as DatePicker).Text);
        }
    }

    public class AdaptiveXceedTimeInputValue : AdaptiveTimeInputValue
    {
        public AdaptiveXceedTimeInputValue(AdaptiveTimeInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

        public override string GetValue()
        {
            return ToIso8601Time((RenderedInputElement as TimePicker).Text);
        }
    }

}
