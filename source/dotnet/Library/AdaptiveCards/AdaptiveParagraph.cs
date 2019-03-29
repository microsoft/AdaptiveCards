using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveParagraph
    {
        [JsonRequired]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveTextRun>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveTextRun))]
#endif
        public List<AdaptiveTextRun> Inlines { get; set; } = new List<AdaptiveTextRun>();


    }
}
