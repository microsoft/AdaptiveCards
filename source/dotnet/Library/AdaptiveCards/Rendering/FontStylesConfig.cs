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
    }
}
