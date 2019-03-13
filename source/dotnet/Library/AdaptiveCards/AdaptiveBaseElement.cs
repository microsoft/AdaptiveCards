using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    public class AdaptiveInternalID
    {
        public static uint Invalid = 0;
        private static uint CurrentInternalID = 1;
        private uint ID { get; }

        public AdaptiveInternalID()
        {
            ID = Invalid;
        }

        private AdaptiveInternalID(uint id)
        {
            ID = id;
        }

        public static AdaptiveInternalID Current()
        {
            return new AdaptiveInternalID(CurrentInternalID);
        }

        public static AdaptiveInternalID Next()
        {
            CurrentInternalID++;

            // handle overflow case
            if (CurrentInternalID == AdaptiveInternalID.Invalid)
            {
                CurrentInternalID++;
            }

            return Current();
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }

            return ((AdaptiveInternalID)obj).ID == this.ID;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }

    public class AdaptiveFallbackElement
    {
        public static readonly string drop = "drop";

        public enum AdaptiveFallbackType
        {
            None,
            Drop,
            Content
        }

        public AdaptiveFallbackElement(AdaptiveFallbackType type)
        {
            if (type == AdaptiveFallbackType.Content)
            {
                throw new ArgumentException("type", "\"type\" cannot be AdaptiveFallbackType.Content. Use AdaptiveFallbackElement(AdaptiveTypedElement)");
            }
            Type = type;
            FallbackContent = null;
        }

        public AdaptiveFallbackElement(AdaptiveTypedElement elem)
        {
            if (elem == null)
            {
                throw new ArgumentNullException("elem");
            }
            else
            {
                Type = AdaptiveFallbackType.Content;
                FallbackContent = elem;
            }
        }

        public AdaptiveFallbackType Type
        {
            get { return Type; }
            set
            {
                if (value == AdaptiveFallbackType.Content)
                {
                    throw new ArgumentException("type", "\"type\" cannot be AdaptiveFallbackType.Content. Set AdaptiveFallbackElement.FallbackContent");
                }
                Type = value;
            }
        }

        public AdaptiveTypedElement FallbackContent
        {
            get { return FallbackContent; }
            set
            {
                Type = (value == null) ? AdaptiveFallbackType.Content : AdaptiveFallbackType.Drop;
                FallbackContent = value;
            }
        }
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public abstract class AdaptiveBaseElement
    {
        [JsonConverter(typeof(AdaptiveFallbackConverter))]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
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

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [DefaultValue(null)]
        public IDictionary<string, AdaptiveSchemaVersion> Requires;

        // Given a map of what our host provides, determine if this element's requirements are satisfied.
        public bool MeetsRequirements(IDictionary<string, string> hostProvides)
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
            return true;
        }
    }
}
