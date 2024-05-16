// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// ContainerStylesConfig
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ContainerStylesConfig
    {
        /// <summary>
        /// Default Style config
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Default { get; set; } = new ContainerStyleConfig();

        /// <summary> 
        /// Emphasis style config
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Emphasis { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#08000000"
        };

        /// <summary>
        /// Good style confing
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Good { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#ffd5f0dd",
            ForegroundColors = alternateForegroundColors
        };


        /// <summary>
        /// Warning style config
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Warning { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#f7f7df",
            ForegroundColors = alternateForegroundColors
        };

        /// <summary>
        /// Attention style config
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ContainerStyleConfig Attention { get; set; } = new ContainerStyleConfig()
        {
            BackgroundColor = "#f7e9e9",
            ForegroundColors = alternateForegroundColors
        };

        /// <summary>
        /// Accent style config
        /// </summary>
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

        /// <summary>
        /// Given a style return the config for the style.
        /// </summary>
        /// <param name="style">style to lookup</param>
        /// <returns>configuration for that style.</returns>
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
