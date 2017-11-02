using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FactSetConfig
    {

        /// <summary>
        /// TextBlock to use for Titles in factsets
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextBlockConfig Title { get; set; } = new TextBlockConfig() { Size = AdaptiveTextSize.Default, Color = AdaptiveTextColor.Default, IsSubtle = false, Weight = AdaptiveTextWeight.Bolder };

        /// <summary>
        /// TextBlock to use for Values in fact sets
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextBlockConfig Value { get; set; } = new TextBlockConfig();

        /// <summary>
        /// Spacing between facts and values
        /// </summary>
        public int Spacing { get; set; } = 10;
    }
}
