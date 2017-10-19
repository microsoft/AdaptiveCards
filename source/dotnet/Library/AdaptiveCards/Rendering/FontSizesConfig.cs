using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontSizesConfig
    {
        public FontSizesConfig() { }

        public int Small { get; set; } = 10;

        public int Default { get; set; } = 12;

        public int Medium { get; set; } = 14;

        public int Large { get; set; } = 17;

        public int ExtraLarge { get; set; } = 20;

    }
}
