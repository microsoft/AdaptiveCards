using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public abstract class AdaptiveTypedElement : ObservableObject
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
        public string Id { get { return _Id; } set { SetPropertyValue(ref _Id, value); } }
        private string _Id = "Z"+Guid.NewGuid().ToString("n");

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

        public virtual IEnumerable<AdaptiveElement> GetAllElements()
        {
            yield break;
        }

        /// <summary>
        /// If this is a container (container, columnset, card) then this is the active list of child elements
        /// </summary>
        /// <returns></returns>
        public virtual IList<AdaptiveElement> GetChildElements()
        {
            return null;
        }

    }
}