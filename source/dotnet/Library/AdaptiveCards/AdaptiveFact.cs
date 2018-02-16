using System;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Represents one "fact" in a FactSet element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [XmlType(TypeName = "Fact")]
    public class AdaptiveFact
    {
        public AdaptiveFact()
        { }

        public AdaptiveFact(string title, string value)
        {
            Title = title;
            Value = value;
        }

        /// <summary>
        ///     The facts label
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Title { get; set; }

        /// <summary>
        ///     The fact's value
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Value { get; set; }

        /// <summary>
        ///     (Optional) Specifies what should be spoken for this entire element. This is simple text or SSML fragment
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("FactSet.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }
    }
}