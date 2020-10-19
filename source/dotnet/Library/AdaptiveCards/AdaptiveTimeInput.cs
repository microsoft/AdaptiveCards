// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Input.Time element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTimeInput.TypeName)]
#endif
    public class AdaptiveTimeInput : AdaptiveInput
    {
        /// <inheritdoc />
        public const string TypeName = "Input.Time";

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
        /// Hint of minimum value (may be ignored by some clients).
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Min { get; set; }

        /// <summary>
        /// Hint of maximum value (may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Max { get; set; }

        /// <inheritdoc />
        public override string GetNonInteractiveValue()
        {
            return Value ?? $"*[{Placeholder}]*";
        }
    }
}
