using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveHostConfig
    {
        public AdaptiveHostConfig() { }

        public static AdaptiveHostConfigParseResult FromJson(string json)
        {
            AdaptiveHostConfig hostConfig = null;

            try
            {
                hostConfig = JsonConvert.DeserializeObject<AdaptiveHostConfig>(json);
            }
            catch
            {
                // TODO: return errors
            }

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
        public string FontFamily { get; set; } = "Calibri";

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
                case AdaptiveCards.AdaptiveSpacing.Small:
                    return Spacing.Small;

                case AdaptiveCards.AdaptiveSpacing.Default:
                    return Spacing.Default;

                case AdaptiveCards.AdaptiveSpacing.Medium:
                    return Spacing.Medium;

                case AdaptiveCards.AdaptiveSpacing.Large:
                    return Spacing.Large;

                case AdaptiveCards.AdaptiveSpacing.ExtraLarge:
                    return Spacing.ExtraLarge;

                case AdaptiveCards.AdaptiveSpacing.Padding:
                    return Spacing.Padding;

                default:
                    throw new NotImplementedException();
            }
        }
    }   
}

