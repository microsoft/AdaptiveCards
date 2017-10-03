using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Text;
using AdaptiveCards.Rendering;

namespace AdaptiveCards.Rendering.Config
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class HostConfig
    {
        public HostConfig() { }

        public static HostConfigParseResult FromJson(string json)
        {
            HostConfig hostConfig = null;

            try
            {
                hostConfig = JsonConvert.DeserializeObject<HostConfig>(json);
            }
            catch { }

            return new HostConfigParseResult(hostConfig);
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

        public int GetSpacing(Spacing spacing)
        {
            switch (spacing)
            {
                case AdaptiveCards.Spacing.Small:
                    return Spacing.Small;

                case AdaptiveCards.Spacing.Default:
                    return Spacing.Default;

                case AdaptiveCards.Spacing.Medium:
                    return Spacing.Medium;

                case AdaptiveCards.Spacing.Large:
                    return Spacing.Large;

                case AdaptiveCards.Spacing.ExtraLarge:
                    return Spacing.ExtraLarge;

                case AdaptiveCards.Spacing.Padding:
                    return Spacing.Padding;

                default:
                    throw new NotImplementedException();
            }
        }
    }   
}

