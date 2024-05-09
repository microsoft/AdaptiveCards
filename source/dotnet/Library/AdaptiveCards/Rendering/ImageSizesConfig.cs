// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Defines config for ImageSizes
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSizesConfig
    {
        /// <summary>
        /// Small image size config.
        /// </summary>
        public int Small { get; set; } = 40;

        /// <summary>
        /// Medium image size config.
        /// </summary>
        public int Medium { get; set; } = 80;

        /// <summary>
        /// Large image size config.
        /// </summary>
        public int Large { get; set; } = 160;
    }
}
