// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

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
#if !NETSTANDARD1_3
        [XmlEnum("default")]
#endif
        Default,

        /// <summary>
        ///     Forces the text to be rendered in a dark color which is suitable when displayed over a light background
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("dark")]
#endif
        Dark,

        /// <summary>
        ///     Forces the text to be rendered in a light color which is suitable when displayed over a dark background
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("light")]
#endif
        Light,

        /// <summary>
        ///     Accent the text
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("accent")]
#endif
        Accent,

        /// <summary>
        ///     Good (such as green)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("good")]
#endif
        Good,

        /// <summary>
        ///     Warning (such as yellow)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("warning")]
#endif
        Warning,

        /// <summary>
        ///     Highlight as needing attention (such as red)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("attention")]
#endif
        Attention
    }
}
