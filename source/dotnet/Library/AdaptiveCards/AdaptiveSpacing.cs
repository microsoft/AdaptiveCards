// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls the spacing of an element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveSpacing>), true)]
    public enum AdaptiveSpacing
    {
        /// <summary>
        /// Use the default spacing.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("default")]
#endif
        Default,

        /// <summary>
        /// Use no spacing.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("none")]
#endif
        None,

        /// <summary>
        /// Use small spacing.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("small")]
#endif
        Small,

        /// <summary>
        /// Use medium spacing.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("medium")]
#endif
        Medium,

        /// <summary>
        /// Use large spacing.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("large")]
#endif
        Large,

        /// <summary>
        /// Use extra large spacing.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("extraLarge")]
#endif
        ExtraLarge,

        /// <summary>
        /// This results in the same padding that's applied to the card itself.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("padding")]
#endif
        Padding
    }
}
