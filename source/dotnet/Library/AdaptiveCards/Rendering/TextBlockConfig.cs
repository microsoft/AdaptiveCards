using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class TextBlockConfig
    {
        public TextBlockConfig()
        { }

        /// <summary>
        ///  The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextSize Size { get; set; } = TextSize.Default;

        /// <summary>
        ///  The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextWeight Weight { get; set; } = TextWeight.Default;

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
            return Size != TextSize.Default;
        }

        public bool ShouldSerializeColor()
        {
            return Color != TextColor.Default;
        }


        public bool ShouldSerializeWeight()
        {
            return Weight != TextWeight.Default;
        }

        public bool ShouldSerializeIsSubtle()
        {
            return IsSubtle;
        }
    }
}
