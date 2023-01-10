// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the relative size of TextBlock elements
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveTextSize>), true)]
    public enum AdaptiveTextSize
    {
        /// <summary>
        ///     Default text size
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("default")]
#endif
        Default = 0,

        /// <summary>
        ///     Default text size
        /// </summary>
        [Obsolete("TextSize.Normal has been deprecated.  Use Default", false)]
        Normal = 0,

        /// <summary>
        ///     Smallest text size
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("small")]
#endif
        Small = 1,

        /// <summary>
        ///     Slightly larger than default
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("medium")]
#endif
        Medium = 2,

        /// <summary>
        ///     Slightly larger then medium
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("large")]
#endif
        Large = 3,

        /// <summary>
        ///     The largest text size
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("extraLarge")]
#endif
        ExtraLarge = 4
    }
}
