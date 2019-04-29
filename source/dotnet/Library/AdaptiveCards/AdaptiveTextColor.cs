// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the color style of TextBlock Elements
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveTextColor>), true)]
    public enum AdaptiveTextColor
    {
        /// <summary>
        ///     The default color which guarentees appropriate contrast
        /// </summary>
        Default,

        /// <summary>
        ///     Forces the text to be rendered in a dark color which is suitable when displayed over a light background
        /// </summary>
        Dark,

        /// <summary>
        ///     Forces the text to be rendered in a light color which is suitable when displayed over a dark background
        /// </summary>
        Light,

        /// <summary>
        ///     Accent the text
        /// </summary>
        Accent,

        /// <summary>
        ///     Good (such as green)
        /// </summary>
        Good,

        /// <summary>
        ///     Warning (such as yellow)
        /// </summary>
        Warning,

        /// <summary>
        ///     Highlight as needing attention (such as red)
        /// </summary>
        Attention
    }
}
