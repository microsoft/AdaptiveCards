using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects text from the user
    /// </summary>
    [XmlType(TypeName = AdaptiveTextInput.TypeName)]
    public class AdaptiveTextInput : AdaptiveInput
    {
        public const string TypeName = "Input.Text";

        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Placeholder { get; set; }

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Value { get; set; }

        /// <summary>
        ///     Hint of style of input, if client doesn't support the style it will become simple text input
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveTextInputStyle), "text")]
        public AdaptiveTextInputStyle Style { get; set; }

        /// <summary>
        ///     true to collect multiple lines of text(default is false)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool IsMultiline { get; set; }

        /// <summary>
        ///     hint of maximum length characters to collect(may be ignored by some clients)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(0)]
        public int MaxLength { get; set; }

        public override string GetNonInteractiveValue()
        {
            return Value ?? $"*[{Placeholder}]*";
        }
    }
}