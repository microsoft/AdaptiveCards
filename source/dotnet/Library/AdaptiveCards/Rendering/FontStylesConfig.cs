// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontStylesConfig
    {
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Default { get; set; } = new FontStyleConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Monospace { get; set; } = new FontStyleConfig();

        public FontStyleConfig GetFontStyle(AdaptiveFontStyle fontStyle)
        {
            switch (fontStyle)
            {
                case AdaptiveFontStyle.Monospace:
                    return Monospace;
                case AdaptiveFontStyle.Default:
                default:
                    return Default;
            }
        }
    }
}
