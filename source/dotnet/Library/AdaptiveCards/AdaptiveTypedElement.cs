using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public abstract class AdaptiveTypedElement
    {
        /// <summary>
        /// The type name of the element 
        /// </summary>
        [JsonProperty(Order = -10, Required = Required.Always)]
        [JsonRequired]
        public abstract string Type { get; }

        /// <summary>
        /// A unique ID associated with the element. For Inputs the ID will be used as the key for Action.Submit response
        /// </summary>
        [JsonProperty(Order = -9, DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Id { get; set; }
    }
}