// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents an ImageSet element.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveImageSet.TypeName)]
#endif
    public class AdaptiveImageSet : AdaptiveElement
    {
        /// <inheritdoc />
        public const string TypeName = "ImageSet";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Collection of images to display.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveImage), ElementName = AdaptiveImage.TypeName)]
#endif
        public List<AdaptiveImage> Images { get; set; } = new List<AdaptiveImage>();

        /// <summary>
        /// Specifies the <see cref="AdaptiveImageSize"/> of each image in the set.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageSize), "auto")]
        public AdaptiveImageSize ImageSize { get; set; }
    }
}
