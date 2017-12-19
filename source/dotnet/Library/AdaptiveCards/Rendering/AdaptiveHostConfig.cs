using System.Diagnostics;
using Newtonsoft.Json;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveHostConfig : AdaptiveConfigBase
    {
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ActionsConfig Actions { get; set; } = new ActionsConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveCardConfig AdaptiveCard { get; set; } = new AdaptiveCardConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ContainerStylesConfig ContainerStyles { get; set; } = new ContainerStylesConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ImageSizesConfig ImageSizes { get; set; } = new ImageSizesConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ImageSetConfig ImageSet { get; set; } = new ImageSetConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FactSetConfig FactSet { get; set; } = new FactSetConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string FontFamily { get; set; } = "Segoe UI";

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontWeightsConfig FontWeights { get; set; } = new FontWeightsConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public SpacingsConfig Spacing { get; set; } = new SpacingsConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
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


        public static AdaptiveHostConfig FromJson(string json)
        {
            try
            {
                return JsonConvert.DeserializeObject<AdaptiveHostConfig>(json);
            }
            catch (JsonException ex)
            {
                Debugger.Break();
                throw new AdaptiveSerializationException(ex.Message, ex);
            }
        }

        /// <summary>
        ///  Serialize this Host Config to JSON
        /// </summary>
        /// <returns></returns>
        public string ToJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

}

