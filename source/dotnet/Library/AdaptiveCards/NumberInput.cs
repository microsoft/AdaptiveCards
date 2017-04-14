using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects number from the user
    /// </summary>
    public class NumberInput : Input
    {
        public const string TYPE = "Input.Number";

        public NumberInput()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452        
        [XmlAttribute]
#endif
        public string Placeholder { get; set; }

        /// <summary>
        ///     The initial value for the field
        /// </summary>
#if NET452
        [XmlAttribute]
#endif
        public double Value { get; set; } = double.NaN;

        /// <summary>
        ///     hint of minimum value(may be ignored by some clients)
        /// </summary>
#if NET452
        [XmlAttribute]
#endif
        public double Min { get; set; } = double.NaN;

        /// <summary>
        ///     hint of maximum value(may be ignored by some clients)
        /// </summary>
#if NET452
        [XmlAttribute]
#endif
        public double Max { get; set; } = double.NaN;

        bool ShouldSerializeMin() { return Min != double.NaN; }
        bool ShouldSerializeMax() { return Max != double.NaN; }
        bool ShouldSerializeValue() { return Max != double.NaN; }
    }
}