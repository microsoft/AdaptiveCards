// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls which style to apply to a container.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveContainerStyle>), true)]
    public enum AdaptiveContainerStyle
    {
        /// <summary>
        /// The container is a normal container
        /// </summary>
        [Obsolete("ContainerStyle.Normal has been deprecated.  Use ContainerStyle.Default", false)]
        Normal = 0,

        /// <summary>
        /// The container should be displayed using the default style
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("default")]
#endif
        Default = 0,

        /// <summary>
        /// The container should be displayed using the emphasis style
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("emphasis")]
#endif
        Emphasis = 1,

        /// <summary>
        /// The container should be displayed using the good style
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("good")]
#endif
        Good = 2,

        /// <summary>
        /// The container should be displayed using the attention style
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("attention")]
#endif
        Attention = 3,

        /// <summary>
        /// The container should be displayed using the warning style
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("warning")]
#endif
        Warning = 4,

        /// <summary>
        /// The container should be displayed using the accent style
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("accent")]
#endif
        Accent = 5
    }
}
