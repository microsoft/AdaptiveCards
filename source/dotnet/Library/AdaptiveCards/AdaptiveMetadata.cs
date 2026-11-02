using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Metadata structure for adaptive card.
    /// </summary>
    public class AdaptiveMetadata
    {
        /// <summary>
        /// URL that uniquely identifies the card and serves as a browser fallback that can be used by some hosts.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string WebUrl { get; set; }

        /// <summary>
        /// Additional properties not found on the default schema.
        /// </summary>
        [JsonExtensionData]
#if NETSTANDARD1_3
        public Dictionary<string, JsonElement> AdditionalProperties { get; set; } = new Dictionary<string, JsonElement>(StringComparer.OrdinalIgnoreCase);
#else
        // Dictionary<string, JsonElement> used for additional properties with JsonExtensionData
        [XmlElement]
        public Dictionary<string, JsonElement> AdditionalProperties { get; set; } = new Dictionary<string, JsonElement>(StringComparer.OrdinalIgnoreCase);

        /// <summary>
        /// Determines whether the <see cref="AdditionalProperties"/> property should be serialized.
        /// </summary>
        public bool ShouldSerializeAdditionalProperties() => this.AdditionalProperties.Count > 0;
#endif
    }
}
