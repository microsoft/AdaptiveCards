using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class IconPlacementConfig
    {
        public AdaptiveIconPlacement IconPlacement { get; set; } = AdaptiveIconPlacement.AboveTitle;
    }
}
