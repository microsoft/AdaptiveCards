using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Config
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColumnConfig
    {
        public ColumnConfig() { }

        /// <summary>
        /// Separation settings between elements
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SeparationConfig Separation { get; set; } = new SeparationConfig() { Spacing = 10 };
    }

}
