// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     The Media element allows for the inclusion of medias (videos and audios) in an Adaptive Card.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = TypeName)]
#endif
    public class AdaptiveMedia : AdaptiveElement
    {
        public const string TypeName = "Media";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     The media sources to try
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveMediaSource), ElementName = "MediaSource")]
#endif
        public List<AdaptiveMediaSource> Sources { get; set; } = new List<AdaptiveMediaSource>();

        /// <summary>
        ///     Poster URL for this media
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Poster { get; set; }

        /// <summary>
        ///     Alternate text to display for this media
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string AltText { get; set; }
    }
}
