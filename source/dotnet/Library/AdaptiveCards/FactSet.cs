using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     The FactSet element makes it simple to display a se ries of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
    public class FactSet : CardElement
    {
        public const string TYPE = "FactSet";

        public FactSet()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlElement(ElementName="Fact", Type=typeof(Fact))]
#endif
        public List<Fact> Facts { get; set; } = new List<Fact>();
    }

    /// <summary>
    ///     Represents one "fact" in a FactSet element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class Fact
    {
        public Fact()
        {
        }

        public Fact(string title, string value, string speak = null)
        {
            Title = title;
            Value = value;
            Speak = speak;
        }

        /// <summary>
        ///     The facts label
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlAttribute]
#endif
        public string Title { get; set; }

        /// <summary>
        ///     The fact's value
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlAttribute]
#endif
        public string Value { get; set; }

        /// <summary>
        ///     (Optional) Specifies what should be spoken for this entire element. This is simple text or SSML fragment
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlElement]
#endif
        public string Speak { get; set; }
    }
}