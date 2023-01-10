// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Defines the vertical alignment behavior of an element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveVerticalAlignment>), true)]
    public enum AdaptiveVerticalAlignment
    {
        /// <summary>
        /// Align to the top.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("top")]
#endif
        Top,

        /// <summary>
        /// Centered.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("center")]
#endif
        Center,

        /// <summary>
        /// Align to the bottom.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("bottom")]
#endif
        Bottom
    }
}
