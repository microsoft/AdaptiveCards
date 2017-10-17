using System.Collections.Generic;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The ImageSet allows for the inclusion of a collection images like a photogallery.
    /// </summary>
    public class AdaptiveImageSet : AdaptiveElement
    {
        public const string TypeName = "ImageSet";

        public AdaptiveImageSet()
        {
            Type = TypeName;
        }

        /// <summary>
        ///     Collection of images to display together
        /// </summary>
        [JsonRequired]
        public List<AdaptiveImage> Images { get; set; } = new List<AdaptiveImage>();

        /// <summary>
        ///     Specifies the horizontal size of each image in the set
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveImageSize ImageSize { get; set; }

        public bool ShouldSerializeImageSize()
        {
            return ImageSize != AdaptiveImageSize.Auto;
        }
    }
}