using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        public ImageStyle Style { get; set; } = ImageStyle.Normal;

        /// <summary>
        /// A url pointing to an image to display
        /// </summary>
        public string Url { get; set; }
    }
}
