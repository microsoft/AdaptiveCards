// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Class to for authentication data.
    /// </summary>
    public class AdaptiveAuthentication
    {
        /// <summary>
        ///     Text that can be displayed to the end user when prompting them to authenticate.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        public string Text { get; set; }

        /// <summary>
        ///     The identifier for registered OAuth connection setting information.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        public string ConnectionName { get; set; }

        /// <summary>
        ///     Provides information required to enable on-behalf-of single sign-on user authentication.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement(typeof(AdaptiveTokenExchangeResource))]
        public AdaptiveTokenExchangeResource TokenExchangeResource { get; set; }

        /// <summary>
        ///     Buttons that should be displayed to the user when prompting for authentication. The array MUST contain one button of type \"signin\". Other button types are not currently supported.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement(typeof(AdaptiveAuthCardButton))]
        public List<AdaptiveAuthCardButton> Buttons { get; set; } = new List<AdaptiveAuthCardButton>();
    }
}
