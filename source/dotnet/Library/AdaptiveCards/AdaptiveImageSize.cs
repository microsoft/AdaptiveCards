// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the horizontal size (width) of element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveImageSize>))]
    public enum AdaptiveImageSize
    {
        /// <summary>
        ///     The width of the element is optimally chosen depending on the space available in the element's container
        /// </summary>
        Auto,

        /// <summary>
        ///     The width of the element adjusts to match that of its container
        /// </summary>
        Stretch,

        /// <summary>
        ///     Small width
        /// </summary>
        Small,

        /// <summary>
        ///     Medium width
        /// </summary>
        Medium,

        /// <summary>
        ///     Large width
        /// </summary>
        Large
    }
}
