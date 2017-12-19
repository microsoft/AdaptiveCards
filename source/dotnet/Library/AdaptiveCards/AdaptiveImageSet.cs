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
    
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Collection of images to display together
        /// </summary>
        [JsonRequired]
        public List<AdaptiveImage> Images { get; set; } = new List<AdaptiveImage>();

        /// <summary>
        ///     Specifies the horizontal size of each image in the set
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveImageSize ImageSize { get; set; }
    }
}