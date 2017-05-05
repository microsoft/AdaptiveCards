using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;


namespace AdaptiveCards.Rendering.Config
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ContainerStyleConfig
    {
        public ContainerStyleConfig() { }

        /// <summary>
        /// Separation settings between elements
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SeparationConfig Separation { get; set; } = new SeparationConfig() { Spacing = 10 };


        /// <summary>
        /// The background color to use for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundColor { get; set; } = "#00FFFFFF";

        /// <summary>
        /// The padding to put on this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SpacingDefinition Padding { get; set; } = new SpacingDefinition(0, 0, 0, 0);

        /// <summary>
        /// The color to use for the border of this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string BorderColor { get; set; } = "#00FFFFFF";

        /// <summary>
        /// The thickness of the border for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SpacingDefinition BorderThickness { get; set; } = new SpacingDefinition(0,0,0,0);
    }
}
