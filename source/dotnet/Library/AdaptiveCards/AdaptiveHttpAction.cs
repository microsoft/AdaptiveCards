// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Action.Http element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveHttpAction.TypeName)]
#endif
    public class AdaptiveHttpAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.Http";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Http method.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Method { get; set; }

		/// <summary>
        /// Target url for request.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Url { get; set; }

		/// <summary>
        /// Body of request.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Body { get; set; }

		/// <summary>
        /// List of headers.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public List<AdaptiveHttpHeader> Headers { get; set; }
		
		/// <summary>
		/// Adds a <see cref="AdaptiveHttpHeader" /> to the AdaptiveHttpAction.
		/// </summary>
		public  void AddHttpHeader(AdaptiveHttpHeader header)
        {
            this.Headers ??= new List<HttpHeader>();
			this.Headers.Add(httpHeader);
        }
    }
}
