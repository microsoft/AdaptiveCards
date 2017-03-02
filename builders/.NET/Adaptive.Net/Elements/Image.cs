using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace Adaptive
{
    /// <summary>
    /// The Image element allows for the inclusion of images in an Adaptive Card.
    /// </summary>
    public partial class Image : CardElement
    {
        public Image()
        { }

        /// <summary>
        /// Size for the Image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public ImageSize Size { get; set; }

        /// <summary>
        /// The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public ImageStyle Style { get; set; }

        /// <summary>
        /// A url pointing to an image to display
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Url { get; set; }

        /// <summary>
        /// Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public HorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        /// Action for this image (this allows a default action to happen when a click on an image happens)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionBase SelectAction { get; set; }

        /// <summary>
        /// Alternate text to display for this image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string AltText { get; set; }

        public bool ShouldSerializeSize() { return this.Size != ImageSize.Auto; }
        public bool ShouldSerializeStyle() { return this.Style != ImageStyle.Normal; }
        public bool ShouldSerializeHorizontalAlignment() { return this.HorizontalAlignment != HorizontalAlignment.Left; }
    }
}
