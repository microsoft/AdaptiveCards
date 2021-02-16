// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.ComponentModel;
using System.Globalization;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Input.Number element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveNumberInput.TypeName)]
#endif
    public class AdaptiveNumberInput : AdaptiveInput
    {
        /// <inheritdoc />
        public const string TypeName = "Input.Number";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Text to display as a placeholder.
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
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(double.NaN)]
        public double Value { get; set; } = double.NaN;

        /// <summary>
        /// Hint of minimum value (may be ignored by some clients).
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(double.NaN)]
        public double Min { get; set; } = double.NaN;

        /// <summary>
        /// Hint of maximum value (may be ignored by some clients).
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(double.NaN)]
        public double Max { get; set; } = double.NaN;

        /// <inheritdoc />
        public override string GetNonInteractiveValue()
        {
            return double.IsNaN(Value)
                ? Value.ToString(CultureInfo.InvariantCulture)
                : $"*[{Placeholder}]*";
        }
    }
}
