using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveCardConfig : AdaptiveConfigBase
    {
        public bool AllowCustomStyle { get; set; }
    }
}