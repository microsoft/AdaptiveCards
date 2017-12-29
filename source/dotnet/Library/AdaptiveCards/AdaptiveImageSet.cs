using System.Collections.Generic;
using System.Collections.ObjectModel;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The ImageSet allows for the inclusion of a collection images like a photogallery.
    /// </summary>
    public class AdaptiveImageSet : AdaptiveElement
    {
        public const string TypeName = "ImageSet";

        public override string Type => TypeName;

        /// <summary>
        ///     Collection of images to display together
        /// </summary>
        [JsonRequired]
        public ObservableCollection<AdaptiveImage> Images { get { return _Images; } set { SetPropertyValue(ref _Images, value); } }
        private ObservableCollection<AdaptiveImage> _Images = new ObservableCollection<AdaptiveImage>();

        /// <summary>
        ///     Specifies the horizontal size of each image in the set
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveImageSize ImageSize { get { return _ImageSize; } set { _ImageSize = value; FirePropertyChanged(); } }
        private AdaptiveImageSize _ImageSize;

        public bool ShouldSerializeImageSize()
        {
            return ImageSize != AdaptiveImageSize.Auto;
        }
    }
}