// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    /// <summary>
    /// Config for ImageSets
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class ImageSetConfig
    {
        /// <summary>
        /// Define default image size for ImageSets.
        /// </summary>
        public AdaptiveImageSize ImageSize { get; set; } = AdaptiveImageSize.Medium;
    }

}
