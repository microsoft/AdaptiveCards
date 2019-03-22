using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

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
        [XmlIgnore]
#endif
        public abstract string Type { get; set; }

        /// <summary>
        /// Additional properties not found on the default schema
        /// </summary>
        [JsonExtensionData]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public IDictionary<string, object> AdditionalProperties { get; set; } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);

        [JsonIgnore]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveFallbackElement Fallback { get; set; }

        [JsonIgnore]
        public AdaptiveInternalID InternalID { get; }

        /// <summary>
        /// A unique ID associated with the element. For Inputs the ID will be used as the key for Action.Submit response
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Id { get; set; }

        [JsonProperty(Order = 1, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public IDictionary<string, AdaptiveSchemaVersion> Requires;

        // Given a map of what our host provides, determine if this element's requirements are satisfied.
        public bool MeetsRequirements(IDictionary<string, string> hostProvides)
        {
            if (Requires != null)
            {
                foreach (var requirement in Requires)
                {
                    // special case for adaptive cards version
                    var requirementName = requirement.Key;
                    var requirementVersion = requirement.Value;
                    if (requirementName.Equals("adaptiveCards"))
                    {
                        AdaptiveSchemaVersion currentAdaptiveCardsVersion = new AdaptiveSchemaVersion("1.2");
                        if (currentAdaptiveCardsVersion > requirementVersion)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        string provides;
                        if (!hostProvides.TryGetValue(requirementName, out provides))
                        {
                            // host doesn't provide this requirement
                            return false;
                        }
                        else
                        {
                            // host provides this requirement, but does it provide an acceptible version?
                            var providesVersion = new AdaptiveSchemaVersion(provides);
                            if (providesVersion < requirementVersion)
                            {
                                // host's provided version is too low
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        }
    }
}
