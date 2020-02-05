// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the way Image elements are displayed.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveImageStyle>), true)]
    public enum AdaptiveImageStyle
    {
        /// <summary>
        ///     The image is displayed within a rectangle.
        /// </summary>
        Default = 0,

        /// <summary>
        ///     The image is displayed within a rectangle.
        /// </summary>
        [Obsolete("ImageStyle.Normal has been deprecated.  Use ImageStyle.Default", false)]
        Normal = 0,

        /// <summary>
        ///     The image is cropped to a circle, a common way to represent people photos.
        /// </summary>
        Person = 1
    }
}
