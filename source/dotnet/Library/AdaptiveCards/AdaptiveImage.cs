using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     The Image element allows for the inclusion of images in an Adaptive Card.
    /// </summary>
    public class AdaptiveImage : AdaptiveElement
    {
        public const string TypeName = "Image";

        public AdaptiveImage()
        {
            Type = TypeName;
        }

        /// <summary>
        ///     Size for the Image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveImageSize Size { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveImageStyle Style { get; set; }

        /// <summary>
        ///     A url pointing to an image to display
        /// </summary>
        [JsonRequired]
        public string Url { get; set; }

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     Action for this image (this allows a default action to happen when a click on an image happens)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveActionBase SelectAction { get; set; }

        /// <summary>
        ///     Alternate text to display for this image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string AltText { get; set; }

        public bool ShouldSerializeSize()
        {
            return Size != AdaptiveImageSize.Auto;
        }

        public bool ShouldSerializeStyle()
        {
            return Style != AdaptiveImageStyle.Default;
        }

        public bool ShouldSerializeHorizontalAlignment()
        {
            return HorizontalAlignment != AdaptiveHorizontalAlignment.Left;
        }
    }
}