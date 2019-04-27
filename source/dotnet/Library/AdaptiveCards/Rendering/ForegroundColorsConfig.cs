// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ForegroundColorsConfig
    {

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Default { get; set; } = new FontColorConfig("#FF000000");

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Accent { get; set; } = new FontColorConfig("#FF0000FF");

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Dark { get; set; } = new FontColorConfig("#FF101010");

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Light { get; set; } = new FontColorConfig("#FFFFFFFF");

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Good { get; set; } = new FontColorConfig("#FF008000");

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Warning { get; set; } = new FontColorConfig("#FFFFD700");

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public FontColorConfig Attention { get; set; } = new FontColorConfig("#FF8B0000");
    }

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontColorConfig
    {
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

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Subtle { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public HighlightColorConfig HighlightColors { get; set; }
    }
}
