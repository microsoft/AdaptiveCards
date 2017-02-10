using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// The Image element allows for the inclusion of images in an Adaptive Card.
    /// </summary>
    public class Image : CardElement
    {
        public Image()
        { }

        /// <summary>
        /// The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageStyle? Style { get; set; }

        /// <summary>
        /// A url pointing to an image to display
        /// </summary>
        [JsonRequired]
        public string Url { get; set; }

        /// <summary>
        /// Action for this image (this allows a default action to happen when a click on an image happens)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public Action Action { get; set; }

    }
}
