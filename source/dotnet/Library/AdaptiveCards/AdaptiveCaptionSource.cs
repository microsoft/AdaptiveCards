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
#if !NETSTANDARD1_3
    [XmlType(TypeName = "CaptionSource")]
#endif
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
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string MimeType { get; set; }

        /// <summary>
        /// The URL of this media source.
        /// </summary>
        [JsonProperty]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Url { get; set; }

        /// <summary>
        /// The caption label for the caption
        /// </summary>
        [JsonProperty]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public string Label { get; set; }
    }
}
