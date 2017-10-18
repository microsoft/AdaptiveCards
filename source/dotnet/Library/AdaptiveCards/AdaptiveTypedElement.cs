using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    [JsonConverter(typeof(AdaptiveTypedElementConverter))]
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveTypedElement
    {
        protected AdaptiveTypedElement()
        {
            Type = GetType().Name;
        }

        [JsonProperty(Order = -10, Required = Required.Always)]
        [JsonRequired]
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