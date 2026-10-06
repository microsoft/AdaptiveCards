// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using System.Text.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Media element.
    /// </summary>
    [XmlType(TypeName = TypeName)]
    public class AdaptiveMedia : AdaptiveElement
    {
        /// <inheritdoc />
        public const string TypeName = "Media";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// A collection of source from which to retrieve the media.
        /// </summary>
        [JsonRequired]
        [XmlElement(Type = typeof(AdaptiveMediaSource), ElementName = "MediaSource")]
        public List<AdaptiveMediaSource> Sources { get; set; } = new List<AdaptiveMediaSource>();

        /// <summary>
        /// URL for the poster image to show for this media element.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Poster { get; set; }

        /// <summary>
        /// Alternate text to display for this media element.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string AltText { get; set; }

        /// <summary>
        /// A collection of captions.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlElement(Type = typeof(AdaptiveCaptionSource), ElementName = "CaptionSource")]
        [DefaultValue(null)]
        public List<AdaptiveCaptionSource> CaptionSources { get; set; } = new List<AdaptiveCaptionSource>();

    }
}
