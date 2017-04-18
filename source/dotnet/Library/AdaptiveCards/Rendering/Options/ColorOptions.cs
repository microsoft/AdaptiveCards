using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering.Options
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColorOptions
    {
        public ColorOptions() { }

        public ColorOption Default { get; set; } = new ColorOption("#FF000000");

        public ColorOption Accent { get; set; } = new ColorOption("#FF0000FF");

        public ColorOption Dark { get; set; } = new ColorOption("#FF101010");

        public ColorOption Light { get; set; } = new ColorOption("#FFFFFFFF");

        public ColorOption Good { get; set; } = new ColorOption("#FF008000");

        public ColorOption Warning { get; set; } = new ColorOption("#FFFFD700");

        public ColorOption Attention { get; set; } = new ColorOption("#FF8B0000");
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ColorOption
    {
        public ColorOption(string normal, string subtle = null)
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
        public string Normal { get; set; }

        public string Subtle { get; set; }
    }
}
