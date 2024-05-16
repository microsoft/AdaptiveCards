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
    public class InputsConfig
    {

        /// <summary>
        /// LabelConfig config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public LabelConfig Label { get; set; } = new LabelConfig();

        /// <summary>
        /// ErrorMessage config
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ErrorMessageConfig ErrorMessage { get; set; } = new ErrorMessageConfig();
    }
}
