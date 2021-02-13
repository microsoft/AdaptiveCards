// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Windows;
using System.Windows.Controls;
using AdaptiveCards;
using AdaptiveCards.Rendering.Wpf;

namespace WpfVisualizer
{
    public class MyCustomRating : AdaptiveElement
    {
        public override string Type { get; set; } = "Rating";

        public double Rating { get; set; }

        public AdaptiveTextSize Size { get; set; }

        public AdaptiveTextColor Color { get; set; }

        public static FrameworkElement Render(MyCustomRating rating, AdaptiveRenderContext context)
        {
            var textBlock = new AdaptiveTextBlock
            {
                Size = rating.Size,
                Color = rating.Color
            };
            for (int i = 0; i < rating.Rating; i++)
            {
                textBlock.Text += "\u2605";
            }
            textBlock.Text += $" ({rating.Rating})";
            return context.Render(textBlock);
        }
    }

    public class MyCustomInput : AdaptiveInput
    {
        public override string Type { get; set; } = "customInput";

        public string Value { get; set; }

        public class CustomInputValue : AdaptiveInputValue
        {
            public CustomInputValue(AdaptiveInput inputElement, UIElement renderedElement) : base(inputElement, renderedElement) { }

            public override string GetValue()
            {
                return ((TextBox)RenderedInputElement).Text;
            }

            public override void SetFocus()
            {
                ((TextBox)RenderedInputElement).Focus();
            }

            public override bool Validate()
            {
                return true;
            }
        }

        public static FrameworkElement Render(MyCustomInput input, AdaptiveRenderContext context)
        {
            var textBox = new TextBox();
            textBox.Text = input.Value;

            context.InputValues.Add(input.Id, new CustomInputValue(input, textBox));

            return textBox;
        }

        public override string GetNonInteractiveValue()
        {
            return Value;
        }
    }
}
