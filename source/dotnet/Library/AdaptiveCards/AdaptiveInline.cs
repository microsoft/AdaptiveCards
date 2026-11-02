// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a single inline text entry.
    /// </summary>
    public abstract class AdaptiveInline
    {
        /// <summary>
        /// The type name of the inline.
        /// </summary>
        [JsonPropertyOrder(-10)]
        [JsonRequired]
        // don't serialize type with xml, because we use element name or attribute for type
        [XmlIgnore]
        public abstract string Type { get; set; }

        /// <inheritdoc />
        [JsonExtensionData]
#if NETSTANDARD1_3
        public Dictionary<string, JsonElement> AdditionalProperties { get; set; } = new Dictionary<string, JsonElement>(StringComparer.OrdinalIgnoreCase);
#else
        // Dictionary<string, JsonElement> used for additional properties with JsonExtensionData
        [XmlElement]
        public Dictionary<string, JsonElement> AdditionalProperties { get; set; } = new Dictionary<string, JsonElement>(StringComparer.OrdinalIgnoreCase);

        /// <inheritdoc />
        public bool ShouldSerializeAdditionalProperties() => this.AdditionalProperties.Count > 0;
#endif
    }
}
