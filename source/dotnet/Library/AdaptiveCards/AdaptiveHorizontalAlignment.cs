// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls how elements are horizontally positioned within their container.
    /// </summary>
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveHorizontalAlignment
    {
        /// <summary>
        ///     The element is left aligned
        /// </summary>
        Left,

        /// <summary>
        ///     The element is centered inside its container
        /// </summary>
        Center,

        /// <summary>
        ///     The element is right aligned
        /// </summary>
        Right,

        /// <summary>
        /// Stretch the actions to fit the containerhrit
        /// </summary>
        Stretch
    }
}
