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
    public class SeparatorConfig
    {
        /// <summary>
        /// If there is a visible line, how thick should the line be
        /// </summary>
        public int LineThickness { get; set; } = 1;

        /// <summary>
        /// If there is a visible color, what color to use
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string LineColor { get; set; } = "#FF707070";

    }

}
