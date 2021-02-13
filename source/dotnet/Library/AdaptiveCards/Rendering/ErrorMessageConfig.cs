// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of media
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ErrorMessageConfig
    {
        /// <summary>
        ///  The text color of the label
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveSpacing Spacing { get; set; } = AdaptiveSpacing.Default;

        /// <summary>
        ///  The text size of the label
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveTextSize Size { get; set; } = AdaptiveTextSize.Default;

        /// <summary>
        ///  The text weight of the label
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveTextWeight Weight { get; set; } = AdaptiveTextWeight.Default;
    }
}
