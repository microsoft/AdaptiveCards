using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    [JsonConverter(typeof(TypedElementConverter))]
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class TypedElement
    {
        protected TypedElement()
        {
            Type = GetType().Name;
        }

        [JsonProperty(Order = -2, NullValueHandling = NullValueHandling.Ignore)]
        [JsonRequired]
#if NET452
        [XmlIgnore]
#endif
        public string Type { get; set; }

        protected EnumT? GetEnum<EnumT>(string value)
            where EnumT : struct
        {
            EnumT val;
            if (Enum.TryParse(value, out val))
                return val;
            return null;
        }

        protected int? GetInt(string value)
        {
            int val;
            if (int.TryParse(value, out val))
                return val;
            return null;
        }

        protected bool? GetBool(string value)
        {
            bool val;
            if (bool.TryParse(value, out val))
                return val;
            return null;
        }
    }
}