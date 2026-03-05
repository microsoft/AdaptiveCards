// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Defines the vertical alignment behavior of an element.
    /// </summary>
    [JsonConverter(typeof(JsonStringEnumConverter))]
    public enum AdaptiveVerticalAlignment
    {
        /// <summary>
        /// Align to the top.
        /// </summary>
        Top,

        /// <summary>
        /// Centered.
        /// </summary>
        Center,

        /// <summary>
        /// Align to the bottom.
        /// </summary>
        Bottom
    }
}
