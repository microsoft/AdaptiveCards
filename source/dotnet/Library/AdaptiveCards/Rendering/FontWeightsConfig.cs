using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontWeightsConfig
    {
        public int Lighter { get; set; } = 200;

        public int Default { get; set; } = 400;

        public int Bolder { get; set; } = 600;
    }
}