// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the horizontal size (width) of element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveImageSize>), true)]
    public enum AdaptiveImageSize
    {
        /// <summary>
        ///     The width of the element is optimally chosen depending on the space available in the element's container
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("auto")]
#endif
        Auto,

        /// <summary>
        ///     The width of the element adjusts to match that of its container
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("stretch")]
#endif
        Stretch,

        /// <summary>
        ///     Small width
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("small")]
#endif
        Small,

        /// <summary>
        ///     Medium width
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("medium")]
#endif
        Medium,

        /// <summary>
        ///     Large width
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("large")]
#endif
        Large
    }
}
