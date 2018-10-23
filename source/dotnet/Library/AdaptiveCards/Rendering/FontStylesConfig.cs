using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontStylesConfig
    {
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Default { get; set; } = new FontStyleConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Display { get; set; } = new FontStyleConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Monospace { get; set; } = new FontStyleConfig();

        public FontStyleConfig GetFontStyle(AdaptiveFontStyle fontStyle)
        {
            switch (fontStyle)
            {
                case AdaptiveFontStyle.Display:
                    return Display;
                case AdaptiveFontStyle.Monospace:
                    return Monospace;
                case AdaptiveFontStyle.Default:
                default:
                    return Default;
            }
        }
    }
}
