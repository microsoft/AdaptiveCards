using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// The ImageSet allows for the inclusion of a collection images like a photogallery.
    /// </summary>
    public class ImageSet : CardItem
    {
        public ImageSet()
        {

        }

        /// <summary>
        /// Collection of images to display together 
        /// </summary>
        [JsonRequired]
        public List<Image> Images { get; set; } = new List<Image>();

        /// <summary>
        /// Specifies the horizontal size of each image in the set
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ImageSize? Size { get; set; }
    }
}
