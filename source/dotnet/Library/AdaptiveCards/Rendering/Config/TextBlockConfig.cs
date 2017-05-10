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
    public class TextConfig
    {
        public TextConfig()
        { }

        /// <summary>
        ///  The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextSize Size { get; set; } = TextSize.Normal;

        /// <summary>
        ///  The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextWeight Weight { get; set; } = TextWeight.Normal;

        /// <summary>
        ///  The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextColor Color { get; set; } = TextColor.Default;

        /// <summary>
        ///   Should it be subtle?
        /// </summary>
        public bool IsSubtle { get; set; } = false;

        /// <summary>
        ///  Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool Wrap { get; set; }

        public bool ShouldSerializeSize()
        {
            return Size != TextSize.Normal;
        }

        public bool ShouldSerializeColor()
        {
            return Color != TextColor.Default;
        }


        public bool ShouldSerializeWeight()
        {
            return Weight != TextWeight.Normal;
        }

        public bool ShouldSerializeIsSubtle()
        {
            return IsSubtle;
        }
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class TextBlockConfig
    {
        public TextBlockConfig()
        { }

        public TextSizeSeparations Separations { get; set; } = new TextSizeSeparations();
    }



    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]

    public class TextSizeSeparations
    {
        public TextSizeSeparations()
        {
        }

        public SeparationConfig Small { get; set; } = new SeparationConfig() { Spacing = 10 };

        public SeparationConfig Normal { get; set; } = new SeparationConfig() { Spacing = 10 };

        public SeparationConfig Medium { get; set; } = new SeparationConfig() { Spacing = 10 };

        public SeparationConfig Large { get; set; } = new SeparationConfig() { Spacing = 10 };

        public SeparationConfig ExtraLarge { get; set; } = new SeparationConfig() { Spacing = 10 };

    }
}
