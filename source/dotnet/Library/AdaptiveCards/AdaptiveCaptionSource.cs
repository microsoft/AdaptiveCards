// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a "media source" for a Media element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [XmlType(TypeName = "CaptionSource")]
    public class AdaptiveCaptionSource
    {
        /// <summary>
        /// Initializes an empty <see cref="AdaptiveMediaSource"/>.
        /// </summary>
        public AdaptiveCaptionSource()
        {
        }

        /// <summary>
        /// Initializes an <see cref="AdaptiveMediaSource"/> instance with the given properties.
        /// </summary>
        /// <param name="mimeType">The mime type of the media.</param>
        /// <param name="url">The url from which to load the media.</param>
        public AdaptiveCaptionSource(string mimeType, string url)
        {
            MimeType = mimeType;
            Url = url;
        }

        /// <summary>
        /// The mime type of this media source.
        /// </summary>
        [JsonProperty]
        [XmlAttribute]
        public string MimeType { get; set; }

        /// <summary>
        /// The URL of this media source.
        /// </summary>
        [JsonProperty]
        [XmlAttribute]
        public string Url { get; set; }

        /// <summary>
        /// The caption label for the caption
        /// </summary>
        [JsonProperty]
        [XmlAttribute]
        public string Label { get; set; }
    }
}
