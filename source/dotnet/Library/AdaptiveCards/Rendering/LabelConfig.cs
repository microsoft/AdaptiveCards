// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of input labels
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class LabelConfig
    {
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public InputLabelConfig RequiredInputs { get; set; } = new InputLabelConfig();

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public InputLabelConfig OptionalInputs { get; set; } = new InputLabelConfig();

        /// <summary>
        /// Specifies the spacing bewteen the label and the input
        /// </summary>
        public AdaptiveSpacing InputSpacing { get; set; }
    }
}
