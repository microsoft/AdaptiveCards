using System.ComponentModel;
using System.Globalization;
using System.Xml.Serialization;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects number from the user
    /// </summary>
    [XmlType(TypeName = AdaptiveNumberInput.TypeName)]
    public class AdaptiveNumberInput : AdaptiveInput
    {
        public const string TypeName = "Input.Number";

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
        [XmlAttribute]
        [DefaultValue(double.NaN)]
        public double Value { get; set; } = double.NaN;

        /// <summary>
        ///     hint of minimum value(may be ignored by some clients)
        /// </summary>
        [XmlAttribute]
        [DefaultValue(double.NaN)]
        public double Min { get; set; } = double.NaN;

        /// <summary>
        ///     hint of maximum value(may be ignored by some clients)
        /// </summary>
        [XmlAttribute]
        [DefaultValue(double.NaN)]
        public double Max { get; set; } = double.NaN;

        public override string GetNonInteractiveValue()
        {
            return double.IsNaN(Value)
                ? Value.ToString(CultureInfo.InvariantCulture)
                : $"*[{Placeholder}]*";
        }
    }
}