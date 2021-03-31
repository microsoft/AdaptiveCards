// Copyright(c) Microsoft Corporation.All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;

using AdaptiveCards.Rendering.Uwp;
using Windows.Data.Json;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace XamlCardVisualizer.CustomElements
{
    public class CustomInput : IAdaptiveInputElement, IAdaptiveCardElement
    {
        public string ErrorMessage { get; set; }
        public bool IsRequired { get; set; }
        public string Label { get; set; }

        public static readonly string customInputType = "customInput";

        public JsonObject ToJson()
        {
            return null;
        }

        public JsonObject AdditionalProperties { get; set; }

        public ElementType ElementType => ElementType.Custom;

        public string ElementTypeString => customInputType;

        public IAdaptiveCardElement FallbackContent { get; set; }
        public FallbackType FallbackType { get; set; }
        public HeightType Height { get; set; }
        public string Id { get; set; }
        public bool IsVisible { get; set; } = true;

        public IList<AdaptiveRequirement> Requirements = new List<AdaptiveRequirement>();

        public bool Separator { get; set; }
        public Spacing Spacing { get; set; }

        IList<AdaptiveRequirement> IAdaptiveCardElement.Requirements => throw new NotImplementedException();
    }


    public class CustomInputParser : IAdaptiveElementParser
    {
        public IAdaptiveCardElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
        {
            CustomInput customInput = new CustomInput();
            customInput.Id = inputJson.GetNamedString("id");
            customInput.Label = inputJson.GetNamedString("label");

            return customInput;
        }
    }

    public class CustomInputRenderer : IAdaptiveElementRenderer
    {
        public UIElement Render(IAdaptiveCardElement element, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
        {
            TextBox textBox = new TextBox { Background = new SolidColorBrush(Windows.UI.Color.FromArgb(255, 0, 255, 0)), HorizontalAlignment = HorizontalAlignment.Right };

            context.AddInputValue(new InputValue(element as CustomInput, textBox), renderArgs);

            return textBox;
        }
    }

    public class InputValue : IAdaptiveInputValue
    {
        public InputValue(CustomInput element, TextBox textBox)
        {
            InputElement = element;
            VisualElement = textBox;
        }

        public bool Validate()
        {
            if (InputElement != null)
            {
                string value = CurrentValue;

                if (InputElement.IsRequired && String.IsNullOrWhiteSpace(value))
                {
                    return false;
                }

                if (!csharpKeywords.Contains(value))
                {
                    return false;
                }

                return true;
            }

            return false;
        }

        public void SetFocus()
        {
            VisualElement.Focus(FocusState.Keyboard);
        }

        public string CurrentValue { get { return VisualElement?.Text ?? ""; } }

        public UIElement ErrorMessage { get; set; }

        public IAdaptiveInputElement InputElement { get; set; }

        public TextBox VisualElement;

        public readonly string[] csharpKeywords = {"abstract", "as", "base", "bool", "break", "byte", "case", "catch", "char", "checked", "class", "const", "continue", "decimal",
                "default", "delegate", "do", "double", "else", "enum", "event", "explicit", "extern", "false", "finally", "fixed", "float", "for", "foreach", "goto", "if",
                "implicit", "in", "int", "interface", "internal", "is", "lock", "long", "namespace", "new", "null", "object", "operator", "out", "override", "params", "private",
                "protected", "public", "readonly", "ref", "return", "sbyte", "sealed", "short", "sizeof", "stackalloc", "static", "string", "struct", "switch", "this", "throw",
                "true", "try", "typeof", "uint", "ulong", "unchecked", "unsafe", "ushort", "using", "virtual", "void", "volatile", "while" };
    }
}
