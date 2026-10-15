// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Class for TokenExchangeResource
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveTokenExchangeResource
    {
        /// <summary>
        ///     The unique identifier of this token exchange instance.
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Id { get; set; }

        /// <summary>
        ///     An application ID or resource identifier with which to exchange a token on behalf of.
        ///     This property is identity provider- and application-specific.
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Uri { get; set; }

        /// <summary>
        ///     An identifier for the identity provider with which to attempt a token exchange.
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string ProviderId { get; set; }
    }
}
