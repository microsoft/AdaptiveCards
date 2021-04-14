// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    public class AdaptiveTokenExchangeResource
    {
        /// <summary>
        ///     The unique identifier of this token exchange instance.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Id { get; set; }

        /// <summary>
        ///     An application ID or resource identifier with which to exchange a token on behalf of.
        ///     This property is identity provider- and application-specific.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Uri { get; set; }

        /// <summary>
        ///     An identifier for the identity provider with which to attempt a token exchange.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string ProviderId { get; set; }
    }
}
