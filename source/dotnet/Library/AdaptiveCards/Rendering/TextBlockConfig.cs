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
        public AdaptiveTextSize Size { get; set; } = AdaptiveTextSize.Default;

        /// <summary>
        ///  The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextWeight Weight { get; set; } = AdaptiveTextWeight.Default;

        /// <summary>
        ///  The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextColor Color { get; set; } = AdaptiveTextColor.Default;

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
            return Size != AdaptiveTextSize.Default;
        }

        public bool ShouldSerializeColor()
        {
            return Color != AdaptiveTextColor.Default;
        }


        public bool ShouldSerializeWeight()
        {
            return Weight != AdaptiveTextWeight.Default;
        }

        public bool ShouldSerializeIsSubtle()
        {
            return IsSubtle;
        }
    }
}
