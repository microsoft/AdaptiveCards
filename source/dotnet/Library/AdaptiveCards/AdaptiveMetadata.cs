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

        /// <summary>
        /// Additional properties not found on the default schema.
        /// </summary>
        [JsonExtensionData]
#if NETSTANDARD1_3
        public IDictionary<string, object> AdditionalProperties { get; set; } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);
#else
        // Dictionary<> is not supported with XmlSerialization because Dictionary is not serializable, SerializableDictionary<> is
        [XmlElement]
        public SerializableDictionary<string, object> AdditionalProperties { get; set; } = new SerializableDictionary<string, object>(StringComparer.OrdinalIgnoreCase);

        /// <summary>
        /// Determines whether the <see cref="AdditionalProperties"/> property should be serialized.
        /// </summary>
        public bool ShouldSerializeAdditionalProperties() => this.AdditionalProperties.Count > 0;
#endif
    }
}
