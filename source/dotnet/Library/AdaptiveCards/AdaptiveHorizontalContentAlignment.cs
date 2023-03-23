// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls the horizontal alignment of child elements within a container.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveHorizontalContentAlignment>), true)]
    public enum AdaptiveHorizontalContentAlignment
    {
        /// <summary>
        /// Align to the leading edge of the container.
        /// </summary>
        Left,

        /// <summary>
        /// Center within the container.
        /// </summary>
        Center,

        /// <summary>
        /// Align to the trailing edge of the container.
        /// </summary>
        Right 
    }
}
