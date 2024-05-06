// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// FontStyle config
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontStyleConfig
    {
        /// <summary>
        /// Font family 
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string FontFamily { get; set; }

        /// <summary>
        /// FontSizes Config
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        /// <summary>
        /// FontWeights config
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontWeightsConfig FontWeights { get; set; } = new FontWeightsConfig();
    }
}
