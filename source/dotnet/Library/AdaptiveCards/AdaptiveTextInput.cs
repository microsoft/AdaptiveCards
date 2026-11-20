// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents an Input.Text element.
    /// </summary>
    [XmlType(TypeName = AdaptiveTextInput.TypeName)]
    public class AdaptiveTextInput : AdaptiveInput
    {
        /// <inheritdoc />
        public const string TypeName = "Input.Text";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Placeholder text to display when the input is empty.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Placeholder { get; set; }

        /// <summary>
        /// The initial value for the field.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Value { get; set; }

        /// <summary>
        /// Hint of style of input, if client doesn't support the style it will become simple text input.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveTextInputStyle), "text")]
        public AdaptiveTextInputStyle Style { get; set; }

        /// <summary>
        /// Controls whether multiple lines of text are allowed.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool IsMultiline { get; set; }

        /// <summary>
        /// Hint of maximum number of characters to collect (may be ignored by some clients).
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(0)]
        public int MaxLength { get; set; }

        /// <summary>
        /// <see cref="AdaptiveAction"/> to invoke inline.
        /// </summary>
        [JsonPropertyName("inlineAction")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveExecuteAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
        public AdaptiveAction InlineAction { get; set; }

        /// <inheritdoc />
        public override string GetNonInteractiveValue()
        {
            return Value ?? $"*[{Placeholder}]*";
        }

        /// <summary>
        /// Regular expression used for validating the input.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Regex { get; set; }
    }
}
