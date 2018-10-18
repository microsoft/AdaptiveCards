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
        /// A unique ID associated with the element. For Inputs the ID will be used as the key for Action.Submit response
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Id { get; set; }

        /// <summary>
        /// Additional properties not found on the default schema
        /// </summary>
        [JsonExtensionData]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public IDictionary<string, object> AdditionalProperties { get; set;  } = new Dictionary<string, object>(StringComparer.OrdinalIgnoreCase);

        [JsonConverter(typeof(ThicknessConverter))]
        public AdaptiveThickness MarginFromParent { get; set; }
    }

    public class ThicknessConverter : JsonConverter
    {
        public override bool CanConvert(Type objectType)
        {
            return false;
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            try
            {
                if (reader.TokenType == JsonToken.StartObject)
                {
                    return serializer.Deserialize(reader, objectType);
                }

                // Just a single spacing value
                var val = reader.Value.ToString().ToLower();
                val = val.Substring(0, 1).ToUpper() + val.Substring(1);
                var spacing = (AdaptiveSpacing)Enum.Parse(typeof(AdaptiveSpacing), val);
                return new AdaptiveThickness()
                {
                    Left = spacing,
                    Top = spacing,
                    Right = spacing,
                    Bottom = spacing
                };
            }
            catch { return null; }
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }
}
