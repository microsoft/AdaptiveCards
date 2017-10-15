using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontColorsConfig
    {
        public FontColorsConfig() { }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontColorConfig Default { get; set; } = new FontColorConfig("#FF000000");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontColorConfig Accent { get; set; } = new FontColorConfig("#FF0000FF");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontColorConfig Dark { get; set; } = new FontColorConfig("#FF101010");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontColorConfig Light { get; set; } = new FontColorConfig("#FFFFFFFF");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontColorConfig Good { get; set; } = new FontColorConfig("#FF008000");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontColorConfig Warning { get; set; } = new FontColorConfig("#FFFFD700");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontColorConfig Attention { get; set; } = new FontColorConfig("#FF8B0000");
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontColorConfig
    {
        public FontColorConfig(string normal, string subtle = null)
        {
            this.Normal = normal;
            if (subtle == null)
            {
                var opacity = (byte)(Convert.ToByte(normal.Substring(1, 2), 16) * .7);
                this.Subtle = $"#{opacity.ToString("x")}{normal.Substring(3)}";
            }
            else
                this.Subtle = subtle;
        }

        /// <summary>
        /// Color in #RRGGBB format
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Normal { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Subtle { get; set; }
    }
}
