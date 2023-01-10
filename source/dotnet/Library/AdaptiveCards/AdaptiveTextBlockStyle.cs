// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Indicates TextBlock element's content type.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveTextBlockStyle>), true)]
    public enum AdaptiveTextBlockStyle
    {
        /// <summary>
        ///     The content is a paragraph (default).
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("default")]
#endif
        Default,

        /// <summary>
        ///     The content is a heading.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("heading")]
#endif
        Heading
    }
}
