// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Configuration for HightlightColors
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class HighlightColorConfig
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public HighlightColorConfig()
        {
            this.Default = this.Subtle = "#FFFFFF00";
        }

        /// <summary>
        /// Color in #RRGGBB format
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Default { get; set; }

        /// <summary>
        /// Color config for subtle highlight
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public string Subtle { get; set; }
    }
}
