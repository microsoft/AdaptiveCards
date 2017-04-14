using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     The Image element allows for the inclusion of images in an Adaptive Card.
    /// </summary>
    public class Image : CardElement
    {
        public const string TYPE = "Image";

        public Image()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Size for the Image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public ImageSize Size { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public ImageStyle Style { get; set; }

        /// <summary>
        ///     A url pointing to an image to display
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlAttribute]
#endif
        public string Url { get; set; }

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public HorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     Action for this image (this allows a default action to happen when a click on an image happens)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionBase SelectAction { get; set; }

        /// <summary>
        ///     Alternate text to display for this image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string AltText { get; set; }

        public bool ShouldSerializeSize()
        {
            return Size != ImageSize.Auto;
        }

        public bool ShouldSerializeStyle()
        {
            return Style != ImageStyle.Normal;
        }

        public bool ShouldSerializeHorizontalAlignment()
        {
            return HorizontalAlignment != HorizontalAlignment.Left;
        }
    }
}