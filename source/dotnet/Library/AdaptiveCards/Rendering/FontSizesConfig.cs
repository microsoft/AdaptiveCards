using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontSizesConfig
    {
        public int Small { get; set; } = 12;

        public int Default { get; set; } = 14;

        public int Medium { get; set; } = 17;

        public int Large { get; set; } = 21;

        public int ExtraLarge { get; set; } = 26;

    }
}
