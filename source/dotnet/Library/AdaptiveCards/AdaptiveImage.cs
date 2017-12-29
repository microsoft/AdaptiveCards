using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The Image element allows for the inclusion of images in an Adaptive Card.
    /// </summary>
    public class AdaptiveImage : AdaptiveElement
    {
        public const string TypeName = "Image";

        public override string Type => TypeName;

        /// <summary>
        ///     Size for the Image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveImageSize Size { get { return _Size; } set { SetPropertyValue(ref _Size, value); } }
        private AdaptiveImageSize _Size;

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveImageStyle Style { get { return _Style; } set { SetPropertyValue(ref _Style, value); } }
        private AdaptiveImageStyle _Style;

        /// <summary>
        ///     A url pointing to an image to display
        /// </summary>
        [JsonRequired]
        public string Url { get { return _Url; } set { SetPropertyValue(ref _Url, value); } }
        private string _Url;

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get { return _HorizontalAlignment; } set { SetPropertyValue(ref _HorizontalAlignment, value); } }
        private AdaptiveHorizontalAlignment _HorizontalAlignment;

        /// <summary>
        ///     Action for this image (this allows a default action to happen when a click on an image happens)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveAction SelectAction { get { return _SelectAction; } set { SetPropertyValue(ref _SelectAction, value); } }
        private AdaptiveAction _SelectAction;

        /// <summary>
        ///     Alternate text to display for this image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string AltText { get { return _AltText; } set { _AltText = value; FirePropertyChanged(); } }
        private string _AltText;

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