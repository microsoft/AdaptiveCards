// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls the vertical alignment of child elements within a container.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveVerticalContentAlignment>), true)]
    public enum AdaptiveVerticalContentAlignment
    {
        /// <summary>
        /// Align to the top.
        /// </summary>
        Top,

        /// <summary>
        /// Center within the container.
        /// </summary>
        Center,

        /// <summary>
        /// Align to the bottom of the container.
        /// </summary>
        Bottom
    }
}
