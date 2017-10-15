using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ContainerStylesConfig
    {
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Default { get; set; } = new ContainerStyleConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Emphasis { get; set; } = new ContainerStyleConfig() { };
    }

}
