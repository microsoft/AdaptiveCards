using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Metadata structure for adaptive card.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveMetadata
    {
        /// <summary>
        /// URL that uniquely identifies the card and serves as a browser fallback that can be used by some hosts.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string WebUrl { get; set; }
    }
}
