// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
        public ContainerStyleConfig Emphasis { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#08000000"
        };

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Good { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#ffd5f0dd",
            ForegroundColors = alternateForegroundColors
        };

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Warning { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#f7f7df",
            ForegroundColors = alternateForegroundColors
        };

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Attention { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#f7e9e9",
            ForegroundColors = alternateForegroundColors
        };

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Accent { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#dce5f7",
            ForegroundColors = alternateForegroundColors
        };

        private static readonly ForegroundColorsConfig alternateForegroundColors = new ForegroundColorsConfig()
        {
            Warning = new FontColorConfig("#ffa600", "#B2ffa600")
        };

        public ContainerStyleConfig GetContainerStyleConfig(AdaptiveContainerStyle? style)
        {
            switch (style)
            {
                case AdaptiveContainerStyle.Accent:
                    return Accent;
                case AdaptiveContainerStyle.Warning:
                    return Warning;
                case AdaptiveContainerStyle.Attention:
                    return Attention;
                case AdaptiveContainerStyle.Good:
                    return Good;
                case AdaptiveContainerStyle.Emphasis:
                    return Emphasis;
                case AdaptiveContainerStyle.Default:
                default:
                    return Default;
            }
        }
    }
}
