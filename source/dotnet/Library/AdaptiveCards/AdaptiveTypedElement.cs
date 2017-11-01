using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    //[Serializable]
    public delegate void TypedEventHandler<in TSender, in TEventArgs>(
        TSender sender,
        TEventArgs e
    ) where TEventArgs : EventArgs;

    [JsonConverter(typeof(AdaptiveTypedElementConverter))]
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public abstract class AdaptiveTypedElement
    {
        protected AdaptiveTypedElement()
        {
            Type = GetType().Name;
        }

        /// <summary>
        /// The type name of the element 
        /// </summary>
        [JsonProperty(Order = -10, Required = Required.Always)]
        [JsonRequired]
        public string Type { get; set; }

        /// <summary>
        /// A unique ID associated with the element
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Id { get; set; }


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