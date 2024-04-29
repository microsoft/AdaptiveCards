// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the AdaptiveHttpHeader.
    /// </summary>
    public class AdaptiveHttpHeader
    {
		/// <summary>
        /// Initializes <see cref="AdaptiveHttpHeader"/>.
        /// </summary>
        public AdaptiveHttpHeader(string name, string value)
        {
			Name = name;
			Value = value;
        }

        /// <summary>
        /// Gets or sets the header name.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Name { get; set; }

		/// <summary>
        /// Gets or sets the header value.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Value { get; set; }
    }
}
