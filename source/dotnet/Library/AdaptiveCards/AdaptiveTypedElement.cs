// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [JsonConverter(typeof(AdaptiveTypedElementConverter))]
    public abstract class AdaptiveTypedElement
    {
        /// <summary>
        /// The type name of the element
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

        [JsonConverter(typeof(AdaptiveFallbackConverter))]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveFallbackElement Fallback { get; set; }

        [JsonIgnore]
        public AdaptiveInternalID InternalID { get; }// = ParseContext.PeekElement();

        /// <summary>
        /// A unique ID associated with the element. For Inputs the ID will be used as the key for Action.Submit response
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Id { get; set; }

        /// <summary>
        ///  A collection representing features and feature versions that this element is declared as requiring
        /// </summary>
        [JsonProperty(Order = 1, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public IDictionary<string, string> Requires;

        // Given a map of what our host provides, determine if this element's requirements are satisfied.
        public bool MeetsRequirements(AdaptiveFeatureRegistration featureRegistration)
        {
            if (Requires != null)
            {
                foreach (var requirement in Requires)
                {
                    // special case for adaptive cards version
                    var requirementName = requirement.Key;
                    var requirementVersion = requirement.Value;
                    string provides = featureRegistration.Get(requirementName);
                    if (provides.Length == 0)
                    {
                        return false;
                    }

                    if (requirementVersion == "*")
                    {
                        // any version is sufficient to satisfy the requirement
                        return true;
                    }

                    // host provides this requirement, but does it provide an acceptible version?
                    var providesVersion = new AdaptiveSchemaVersion(provides);
                    if (providesVersion < requirementVersion)
                    {
                        // host's provided version is too low
                        return false;
                    }
                }
            }
            return true;
        }
    }
}
