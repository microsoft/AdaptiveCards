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
    [XmlType(TypeName = AdaptiveImageSet.TypeName)]
    public class AdaptiveImageSet : AdaptiveElement
    {
        /// <inheritdoc />
        public const string TypeName = "ImageSet";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Collection of images to display.
        /// </summary>
        [JsonRequired]
        [XmlElement(typeof(AdaptiveImage), ElementName = AdaptiveImage.TypeName)]
        public List<AdaptiveImage> Images { get; set; } = new List<AdaptiveImage>();

        /// <summary>
        /// Specifies the <see cref="AdaptiveImageSize"/> of each image in the set.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveImageSize), "auto")]
        public AdaptiveImageSize ImageSize { get; set; }
    }
}
