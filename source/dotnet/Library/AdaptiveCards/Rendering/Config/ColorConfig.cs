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
    public class ColorsConfig
    {
        public ColorsConfig() { }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorConfig Default { get; set; } = new ColorConfig("#FF000000");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorConfig Accent { get; set; } = new ColorConfig("#FF0000FF");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorConfig Dark { get; set; } = new ColorConfig("#FF101010");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorConfig Light { get; set; } = new ColorConfig("#FFFFFFFF");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorConfig Good { get; set; } = new ColorConfig("#FF008000");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorConfig Warning { get; set; } = new ColorConfig("#FFFFD700");

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ColorConfig Attention { get; set; } = new ColorConfig("#FF8B0000");
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColorConfig
    {
        public ColorConfig(string normal, string subtle = null)
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
