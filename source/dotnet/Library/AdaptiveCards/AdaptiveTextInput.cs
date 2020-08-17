// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects text from the user
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTextInput.TypeName)]
#endif
    public class AdaptiveTextInput : AdaptiveInput
    {
        public const string TypeName = "Input.Text";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Placeholder { get; set; }

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Value { get; set; }

        /// <summary>
        ///     Hint of style of input, if client doesn't support the style it will become simple text input
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveTextInputStyle), "text")]
        public AdaptiveTextInputStyle Style { get; set; }

        /// <summary>
        ///     true to collect multiple lines of text(default is false)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool IsMultiline { get; set; }

        /// <summary>
        ///     hint of maximum length characters to collect(may be ignored by some clients)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public int MaxLength { get; set; }

        /// <summary>
        /// The Body elements for this card
        /// </summary>
        [JsonProperty("inlineAction", DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveOpenUrlAction))]
        [XmlElement(typeof(AdaptiveShowCardAction))]
        [XmlElement(typeof(AdaptiveSubmitAction))]
        [XmlElement(typeof(AdaptiveToggleVisibilityAction))]
        [XmlElement(typeof(AdaptiveUnknownAction))]
#endif
        public AdaptiveAction InlineAction { get; set; }

        public override string GetNonInteractiveValue()
        {
            return Value ?? $"*[{Placeholder}]*";
        }

        /// <summary>
        /// Regular expression used for validating the input
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Regex { get; set; }
    }
}
