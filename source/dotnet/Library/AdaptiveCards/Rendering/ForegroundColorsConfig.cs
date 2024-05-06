// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Foreground Color Config
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ForegroundColorsConfig
    {
        /// <summary>
        /// Default Config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Default { get; set; } = new FontColorConfig("#FF000000");

        /// <summary>
        /// Accent config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Accent { get; set; } = new FontColorConfig("#FF0000FF");

        /// <summary>
        /// Dark config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Dark { get; set; } = new FontColorConfig("#FF101010");

        /// <summary>
        /// Light config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Light { get; set; } = new FontColorConfig("#FFFFFFFF");

        /// <summary>
        /// Good config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Good { get; set; } = new FontColorConfig("#FF008000");

        /// <summary>
        /// Warning config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Warning { get; set; } = new FontColorConfig("#FFFFD700");

        /// <summary>
        /// Attention config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Attention { get; set; } = new FontColorConfig("#FF8B0000");
    }

    /// <summary>
    /// Font Color config
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontColorConfig
    {
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="defaultColor"></param>
        /// <param name="subtle"></param>
        public FontColorConfig(string defaultColor, string subtle = null)
        {
            this.Default = defaultColor;
            if (subtle == null)
            {
                var opacity = (byte)(Convert.ToByte(defaultColor.Substring(1, 2), 16) * .7);
                this.Subtle = $"#{opacity.ToString("x")}{defaultColor.Substring(3)}";
            }
            else
            {
                this.Subtle = subtle;
            }

            this.HighlightColors = new HighlightColorConfig();

        }

        /// <summary>
        /// Color in #RRGGBB format
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Default { get; set; }

        /// <summary>
        /// Subtle config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Subtle { get; set; }

        /// <summary>
        /// HightlightColors config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public HighlightColorConfig HighlightColors { get; set; }
    }
}
