// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents an Input.Text element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTextInput.TypeName)]
#endif
    public class AdaptiveTextInput : AdaptiveInput
    {
        /// <inheritdoc />
        public const string TypeName = "Input.Text";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Placeholder text to display when the input is empty.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Placeholder { get; set; }

        /// <summary>
        /// The initial value for the field.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Value { get; set; }

        /// <summary>
        /// Hint of style of input, if client doesn't support the style it will become simple text input.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveTextInputStyle), "text")]
        public AdaptiveTextInputStyle Style { get; set; }

        /// <summary>
        /// Controls whether multiple lines of text are allowed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool IsMultiline { get; set; }

        /// <summary>
        /// Hint of maximum number of characters to collect (may be ignored by some clients).
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public int MaxLength { get; set; }

        /// <summary>
        /// <see cref="AdaptiveAction"/> to invoke inline.
        /// </summary>
        [JsonProperty("inlineAction", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
#endif
        public AdaptiveAction InlineAction { get; set; }

        /// <inheritdoc />
        public override string GetNonInteractiveValue()
        {
            return Value ?? $"*[{Placeholder}]*";
        }

        /// <summary>
        /// Regular expression used for validating the input.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Regex { get; set; }
    }
}
