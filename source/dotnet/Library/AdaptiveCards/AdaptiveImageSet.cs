using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The ImageSet allows for the inclusion of a collection images like a photogallery.
    /// </summary>
    [XmlType(TypeName = AdaptiveImageSet.TypeName)]
    public class AdaptiveImageSet : AdaptiveElement
    {
        public const string TypeName = "ImageSet";

        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Collection of images to display together
        /// </summary>
        [JsonRequired]
        [XmlElement(typeof(AdaptiveImage), ElementName = AdaptiveImage.TypeName)]
        public List<AdaptiveImage> Images { get; set; } = new List<AdaptiveImage>();

        /// <summary>
        ///     Specifies the horizontal size of each image in the set
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveImageSize), "auto")]
        public AdaptiveImageSize ImageSize { get; set; }
    }
}