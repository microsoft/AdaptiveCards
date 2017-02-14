using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// The ImageGallery allows for the inclusion of a collection images like a photogallery.
    /// </summary>
    public class ImageGallery : CardElement
    {
        public ImageGallery()
        {

        }

        /// <summary>
        /// Collection of images to display together in the gallery
        /// </summary>
        [JsonRequired]
        public List<Image> Images { get; set; } = new List<Image>();

        /// <summary>
        /// Specifies the horizontal size of each image in the gallery.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageSize? Size { get; set; }
    }
}
