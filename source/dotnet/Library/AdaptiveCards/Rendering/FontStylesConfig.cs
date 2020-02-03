// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontTypesConfig
    {
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Default { get; set; } = new FontStyleConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Monospace { get; set; } = new FontStyleConfig();

        public FontStyleConfig GetFontType(AdaptiveFontType fontType)
        {
            switch (fontType)
            {
                case AdaptiveFontType.Monospace:
                    return Monospace;
                case AdaptiveFontType.Default:
                default:
                    return Default;
            }
        }
    }
}
