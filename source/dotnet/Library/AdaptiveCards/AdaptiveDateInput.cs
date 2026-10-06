// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Input.Date element.
    /// </summary>
    [XmlType(TypeName = AdaptiveDateInput.TypeName)]
    public class AdaptiveDateInput : AdaptiveInput
    {
        /// <inheritdoc />
        public const string TypeName = "Input.Date";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Placeholder text to display.
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
        /// Hint of minimum value (note: may be ignored by some clients).
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Min { get; set; }

        /// <summary>
        /// Hint of maximum value (note: may be ignored by some clients).
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Max { get; set; }

        /// <inheritdoc />
        public override string GetNonInteractiveValue()
        {
            return Value ?? $"*[{Placeholder}]*";
        }
    }
}
