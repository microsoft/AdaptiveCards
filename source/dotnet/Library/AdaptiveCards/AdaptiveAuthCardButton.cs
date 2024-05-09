// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Class for AuthCardButton
    /// </summary>
    public class AdaptiveAuthCardButton
    {
        /// <summary>
        ///     The type of the button.
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Type { get; set; }

        /// <summary>
        ///     The caption of the button.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Title { get; set; }

        /// <summary>
        ///     A URL to an image to display alongside the button's caption.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Image { get; set; }

        /// <summary>
        ///     The value associated with the button. The meaning of value depends on the button's type.
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Value { get; set; }
    }
}
