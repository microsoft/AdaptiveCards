// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class FontStyleConfig
    {
        public FontStyleConfig() { }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string FontFamily { get; set; }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontSizesConfig FontSizes { get; set; } = new FontSizesConfig();

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public FontWeightsConfig FontWeights { get; set; } = new FontWeightsConfig();
    }
}
