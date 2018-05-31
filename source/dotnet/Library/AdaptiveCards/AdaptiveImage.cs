using System;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The Image element allows for the inclusion of images in an Adaptive Card.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveImage.TypeName)]
#endif
    public class AdaptiveImage : AdaptiveElement
    {
        public AdaptiveImage()
        {

        }

        public AdaptiveImage(string url)
        {
            Url = url;
        }

        public const string TypeName = "Image";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Size for the Image
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageSize), "auto")]
        public AdaptiveImageSize Size { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageStyle), "default")]
        public AdaptiveImageStyle Style { get; set; }

        /// <summary>
        ///     A url pointing to an image to display
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Url { get; set; }

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     Action for this image (this allows a default action to happen when a click on an image happens)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        ///     Alternate text to display for this image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string AltText { get; set; }
    }
}