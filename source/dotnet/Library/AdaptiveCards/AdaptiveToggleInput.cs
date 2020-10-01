// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects a choice between two options from the user
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveToggleInput.TypeName)]
#endif
    public class AdaptiveToggleInput : AdaptiveInput
    {
        public const string TypeName = "Input.Toggle";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Title text for toggle
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Title { get; set; }

        /// <summary>
        ///     Value to use for on (Default: true)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string ValueOn { get; set; } = bool.TrueString;

        /// <summary>
        ///     Value to use for off (Default: false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string ValueOff { get; set; } = bool.FalseString;

        /// <summary>
        ///      when set true, text will wrap
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Wrap { get; set; }

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Value { get; set; }

        public override string GetNonInteractiveValue()
        {
            var x = Value == ValueOn ? "X" : " ";
            return $"[{x}] {Title}";
        }
    }
}
