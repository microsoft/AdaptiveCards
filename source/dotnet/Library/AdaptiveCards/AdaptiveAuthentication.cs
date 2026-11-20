// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Collections.Generic;
using System.Net;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Class to for authentication data.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveAuthentication
    {
        /// <summary>
        ///     Text that can be displayed to the end user when prompting them to authenticate.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Text { get; set; } = "Please sign in";

        /// <summary>
        ///     The identifier for registered OAuth connection setting information.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string ConnectionName { get; set; } = "Default";

        /// <summary>
        ///     Provides information required to enable on-behalf-of single sign-on user authentication.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlElement(typeof(AdaptiveTokenExchangeResource))]
        public AdaptiveTokenExchangeResource TokenExchangeResource { get; set; }

        /// <summary>
        ///     Buttons that should be displayed to the user when prompting for authentication. The array MUST contain one button of type \"signin\". Other button types are not currently supported.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlElement(typeof(AdaptiveAuthCardButton))]
        public List<AdaptiveAuthCardButton> Buttons { get; set; } = new List<AdaptiveAuthCardButton>();
    }
}
