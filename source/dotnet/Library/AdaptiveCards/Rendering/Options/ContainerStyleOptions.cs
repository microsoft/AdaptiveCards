using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;


namespace AdaptiveCards.Rendering.Options
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ContainerStyleOptions
    {
        public ContainerStyleOptions() { }

        /// <summary>
        /// Separation settings between elements
        /// </summary>
        public SeparationOptions Separations { get; set; } = new SeparationOptions();

        /// <summary>
        /// The background color to use for this container
        /// </summary>
        public string BackgroundColor { get; set; } = "#00FFFFFF";

        /// <summary>
        /// The padding to put on this container
        /// </summary>
        public SpacingDefinition Padding { get; set; } = new SpacingDefinition(0, 0, 0, 0);

        /// <summary>
        /// The color to use for the border of this container
        /// </summary>
        public string BorderColor { get; set; } = "#00FFFFFF";

        /// <summary>
        /// The thickness of the border for this container
        /// </summary>
        public SpacingDefinition BorderThickness { get; set; } = new SpacingDefinition(0,0,0,0);
    }
}
