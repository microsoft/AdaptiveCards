// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents a "media source" for a Media element.
    /// </summary>
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
        [XmlAttribute]
        public string MimeType { get; set; }

        /// <summary>
        /// The URL of this media source.
        /// </summary>
        [XmlAttribute]
        public string Url { get; set; }

        /// <summary>
        /// The caption label for the caption
        /// </summary>
        [XmlAttribute]
        public string Label { get; set; }
    }
}
