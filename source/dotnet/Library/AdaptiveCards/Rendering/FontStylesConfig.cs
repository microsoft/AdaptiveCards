// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// FontTypes config
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontTypesConfig
    {
        /// <summary>
        /// Default config
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Default { get; set; } = new FontStyleConfig();

        /// <summary>
        /// Monospace congfig
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontStyleConfig Monospace { get; set; } = new FontStyleConfig();

        /// <summary>
        /// Given a fontType get the fontstyle config for ti.
        /// </summary>
        /// <param name="fontType"></param>
        /// <returns></returns>
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
