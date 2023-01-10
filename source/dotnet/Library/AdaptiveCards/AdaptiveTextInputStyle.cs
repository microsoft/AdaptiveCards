// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Style of text input.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveTextInputStyle>), true)]
    public enum AdaptiveTextInputStyle
    {
        /// <summary>
        /// Unstructured plain text.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("text")]
#endif
        Text,

        /// <summary>
        /// Input is a telephone number. The client may use this information to provide optimized keyboard input for the
        /// user.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("tel")]
#endif
        Tel,

        /// <summary>
        /// Input is a url. The client may use this information to provide optimized keyboard input for the user.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("url")]
#endif
        Url,

        /// <summary>
        /// Input is an email address. The client may use this information to provide optimized keyboard input for the user.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("email")]
#endif
        Email,

        /// <summary>
        /// Password 
        /// </summary>
#if !NETSTANDARD1_3
        [XmlEnum("password")]
#endif
        Password
    }
}
