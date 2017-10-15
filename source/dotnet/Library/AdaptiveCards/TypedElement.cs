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

        [JsonProperty(Order = -2, Required = Required.Always)]
        [JsonRequired]
#if NET452
        [XmlIgnore]
#endif
        public string Type { get; set; }

        protected TENum? GetEnum<TENum>(string value)
            where TENum : struct
        {
            if (Enum.TryParse(value, out TENum val))
                return val;
            return null;
        }

        protected int? GetInt(string value)
        {
            if (int.TryParse(value, out var val))
                return val;
            return null;
        }

        protected bool? GetBool(string value)
        {
            if (bool.TryParse(value, out var val))
                return val;
            return null;
        }
    }
}