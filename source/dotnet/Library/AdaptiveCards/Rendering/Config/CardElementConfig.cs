using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Config
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class CardElementConfig
    {
        public CardElementConfig() { }

        /// <summary>
        /// Separation settings between elements
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SeparationConfig Separation { get; set; } = new SeparationConfig() { Spacing = 10 };
    }
}
