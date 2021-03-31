// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public abstract class AdaptiveInline
    {
        /// <summary>
        /// The type name of the inline
        /// </summary>
        [JsonProperty(Order = -10, Required = Required.Always, DefaultValueHandling = DefaultValueHandling.Include)]
#if !NETSTANDARD1_3
        // don't serialize type with xml, because we use element name or attribute for type
        [XmlIgnore]
#endif
        public abstract string Type { get; set; }

        /// <summary>
        /// Additional properties not found on the default schema
        /// </summary>
        [JsonExtensionData]
#if NETSTANDARD1_3
        public IDictionary<string, object> AdditionalProperties { get; set; } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);
#else
        // Dictionary<> is not supported with XmlSerialization because Dictionary is not serializable, SerializableDictionary<> is
        [XmlElement]
        public SerializableDictionary<string, object> AdditionalProperties { get; set; } = new SerializableDictionary<string, object>(StringComparer.OrdinalIgnoreCase);
        public bool ShouldSerializeAdditionalProperties() => this.AdditionalProperties.Count > 0;
#endif
    }
}
