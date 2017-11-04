using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveHostConfig
    {
        public static AdaptiveHostConfigParseResult FromJson(string json)
        {
            var hostConfig = JsonConvert.DeserializeObject<AdaptiveHostConfig>(json);
            return new AdaptiveHostConfigParseResult(hostConfig);
        }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionsConfig Actions { get; set; } = new ActionsConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStylesConfig ContainerStyles { get; set; } = new ContainerStylesConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageSizesConfig ImageSizes { get; set; } = new ImageSizesConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageSetConfig ImageSet { get; set; } = new ImageSetConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FactSetConfig FactSet { get; set; } = new FactSetConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string FontFamily { get; set; } = "Segoe UI";

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SpacingsConfig Spacing { get; set; } = new SpacingsConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public SeparatorConfig Separator { get; set; } = new SeparatorConfig();

        /// <summary>
        /// Toggles whether or not to render inputs and actions
        /// </summary>
        public bool SupportsInteractivity { get; set; } = true;

        public int GetSpacing(AdaptiveSpacing spacing)
        {
            switch (spacing)
            {
                case AdaptiveSpacing.None:
                    return 0;

                case AdaptiveSpacing.Small:
                    return Spacing.Small;

                case AdaptiveSpacing.Medium:
                    return Spacing.Medium;

                case AdaptiveSpacing.Large:
                    return Spacing.Large;

                case AdaptiveSpacing.ExtraLarge:
                    return Spacing.ExtraLarge;

                case AdaptiveSpacing.Padding:
                    return Spacing.Padding;

                default:
                    return Spacing.Default;
            }
        }
    }
}

