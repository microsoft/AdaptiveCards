// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    public partial class AdaptiveFallbackElement
    {
        /// <summary>
        /// Enumeration describing an object's fallback type.
        /// </summary>
        [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveFallbackType>), true)]
        public enum AdaptiveFallbackType
        {
            /// <summary>
            /// This object does not have fallback specified.
            /// </summary>
#if !NETSTANDARD1_3
            [XmlEnum("none")]
#endif
            None,

            /// <summary>
            /// Drop this element during fallback.
            /// </summary>
#if !NETSTANDARD1_3
            [XmlEnum("drop")]
#endif
            Drop,

            /// <summary>
            /// This element has content to show in the event of fallback being triggered.
            /// </summary>
#if !NETSTANDARD1_3
            [XmlEnum("content")]
#endif
            Content
        }
    }
}
