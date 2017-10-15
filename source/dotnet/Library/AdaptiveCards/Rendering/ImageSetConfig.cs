using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSetConfig
    {
        public ImageSetConfig() { }

        public ImageSize ImageSize { get; set; } = ImageSize.Medium;
    }

}
