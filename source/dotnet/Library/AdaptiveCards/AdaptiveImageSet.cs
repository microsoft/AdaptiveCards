// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The ImageSet allows for the inclusion of a collection images like a photogallery.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveImageSet.TypeName)]
#endif
    public class AdaptiveImageSet : AdaptiveElement
    {
        public const string TypeName = "ImageSet";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Collection of images to display together
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveImage), ElementName = AdaptiveImage.TypeName)]
#endif
        public List<AdaptiveImage> Images { get; set; } = new List<AdaptiveImage>();

        /// <summary>
        ///     Specifies the horizontal size of each image in the set
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageSize), "auto")]
        public AdaptiveImageSize ImageSize { get; set; }
    }
}
