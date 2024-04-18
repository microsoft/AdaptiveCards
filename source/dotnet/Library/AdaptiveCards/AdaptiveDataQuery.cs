using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Data.Query data structure for filtered choicesets.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
#if !NETSTANDARD1_3
    [XmlType("Data.Query")]
#endif
    public class AdaptiveDataQuery
    {
        /// <summary>
        /// separator
        /// </summary>
        [JsonIgnore]
        public const char Separator = '#';

        /// <summary>
        /// Specifies that it's a Data.Query object.
        /// </summary>
        [JsonProperty]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public string Type { get; set; } = "Data.Query";

        /// <summary>
        /// Specifies the name of dataset that is fetched dynamically.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Dataset { get; set; }

        /// <summary>
        /// Populates the input 
        /// </summary>
        [JsonProperty]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Value { get; set; }

        /// <summary>
        /// Populates the suggested page size or number of items to request
        /// </summary>
        [JsonProperty]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public int Count { get; set; }

        /// <summary>
        /// Populates the skip value for paging
        /// </summary>
        [JsonProperty]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public int Skip { get; set; }
    }
}
