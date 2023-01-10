// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls how elements are horizontally positioned within their container.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveHorizontalAlignment>), true)]
    public enum AdaptiveHorizontalAlignment
    {
        /// <summary>
        ///     The element is left aligned
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("left")]
#endif
        Left,

        /// <summary>
        ///     The element is centered inside its container
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("center")]
#endif
        Center,

        /// <summary>
        ///     The element is right aligned
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("right")]
#endif
        Right,

        /// <summary>
        /// Stretch the actions to fit the containerhrit
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("stretch")]
#endif
        Stretch
    }
}
