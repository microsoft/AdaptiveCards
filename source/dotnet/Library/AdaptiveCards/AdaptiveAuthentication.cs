// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    public class AdaptiveAuthentication
    {
        /// <summary>
        ///     Text that can be displayed to the end user when prompting them to authenticate.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Text { get; set; }

        /// <summary>
        ///     The identifier for registered OAuth connection setting information.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string ConnectionName { get; set; }

        /// <summary>
        ///     Provides information required to enable on-behalf-of single sign-on user authentication.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveTokenExchangeResource))]
#endif
        public AdaptiveTokenExchangeResource TokenExchangeResource { get; set; }

        /// <summary>
        ///     Buttons that should be displayed to the user when prompting for authentication. The array MUST contain one button of type \"signin\". Other button types are not currently supported.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveAuthCardButton))]
#endif
        public List<AdaptiveAuthCardButton> Buttons { get; set; } = new List<AdaptiveAuthCardButton>();
    }
}
