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
    public class FactSetConfig : CardElementConfig
    {
        public FactSetConfig() { }

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextConfig Title { get; set; } = new TextConfig() { Size = TextSize.Normal, Color = TextColor.Default, IsSubtle = false, Weight = TextWeight.Bolder };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextConfig Value { get; set; } = new TextConfig();

        /// <summary>
        /// Spacing between facts and values
        /// </summary>
        public int Spacing { get; set; } = 20;
    }
}
