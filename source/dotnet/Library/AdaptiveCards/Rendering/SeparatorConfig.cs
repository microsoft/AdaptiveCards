// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class SeparatorConfig
    {
        /// <summary>
        /// If there is a visible line, how thick should the line be
        /// </summary>
        public int LineThickness { get; set; } = 1;

        /// <summary>
        /// If there is a visible color, what color to use
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string LineColor { get; set; } = "#FF707070";

    }

}
