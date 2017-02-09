using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        /// Collection of image objects to display
        /// </summary>
        // ISSUE: Shouldn't this  be called Images since it can only contain Image 
        public List<Image> Items { get; set; } = new List<Image>();

        /// <summary>
        /// Specifies the horizontal size of each image in the gallery.
        /// </summary>
        public Size ImageSize { get; set; } = Size.Medium;
    }
}
