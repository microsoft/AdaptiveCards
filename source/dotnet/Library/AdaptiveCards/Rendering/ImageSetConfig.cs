// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{

    /// <summary>
    /// Config for ImageSets
    /// </summary>
    public class ImageSetConfig
    {
        /// <summary>
        /// Define default image size for ImageSets.
        /// </summary>
        public AdaptiveImageSize ImageSize { get; set; } = AdaptiveImageSize.Medium;
    }

}
