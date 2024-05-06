// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Input.Toggle element.
    /// </summary>
    [XmlType(TypeName = AdaptiveToggleInput.TypeName)]
    public class AdaptiveToggleInput : AdaptiveInput
    {
        /// <inheritdoc />
        public const string TypeName = "Input.Toggle";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Title text for this element.
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Title { get; set; }

        /// <summary>
        /// Value to use when toggle is on.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string ValueOn { get; set; } = bool.TrueString;

        /// <summary>
        /// Value to use when toggle is off.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string ValueOff { get; set; } = bool.FalseString;

        /// <summary>
        /// Controls text wrapping behavior.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Wrap { get; set; }

        /// <summary>
        /// The value for the field.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Value { get; set; }

        /// <inheritdoc />
        public override string GetNonInteractiveValue()
        {
            var x = Value == ValueOn ? "X" : " ";
            return $"[{x}] {Title}";
        }
    }
}
