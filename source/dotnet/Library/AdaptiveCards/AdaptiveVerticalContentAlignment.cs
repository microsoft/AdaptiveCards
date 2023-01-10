// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

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
#if !NETSTANDARD1_3
        [XmlEnum("top")]
#endif
        Top,

        /// <summary>
        /// Center within the container.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("center")]
#endif
        Center,

        /// <summary>
        /// Align to the bottom of the container.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("bottom")]
#endif
        Bottom
    }
}
