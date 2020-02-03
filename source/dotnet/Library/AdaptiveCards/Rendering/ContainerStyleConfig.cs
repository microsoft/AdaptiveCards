// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ContainerStyleConfig
    {
        public ContainerStyleConfig() { }

        /// <summary>
        /// The background color to use for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string BackgroundColor { get; set; } = "#FFFFFFFF";

        /// <summary>
        /// The font colors to use for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ForegroundColorsConfig ForegroundColors { get; set; } = new ForegroundColorsConfig();
    }
}
