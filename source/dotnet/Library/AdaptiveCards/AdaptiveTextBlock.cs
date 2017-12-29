using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive
    ///     Cards.
    /// </summary>
    public class AdaptiveTextBlock : AdaptiveElement
    {
        public const string TypeName = "TextBlock";

        public override string Type => TypeName;

        /// <summary>
        ///     The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextSize Size { get { return _Size; } set { SetValue(ref _Size, value); } }
        private AdaptiveTextSize _Size;

        /// <summary>
        ///     The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextWeight Weight { get { return _Weight; } set { SetValue(ref _Weight, value); } }
        private AdaptiveTextWeight _Weight;

        /// <summary>
        ///     The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextColor Color { get { return _Color; } set { SetValue(ref _Color, value); } }
        private AdaptiveTextColor _Color;

        /// <summary>
        ///     Should it be subtle?
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool IsSubtle { get { return _IsSubtle; } set { SetValue(ref _IsSubtle, value); } }
        private bool _IsSubtle;

        /// <summary>
        ///     The text to display
        /// </summary>
        [JsonRequired]
        public string Text { get { return _Text; } set { SetValue(ref _Text, value); } }
        private string _Text;

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get { return _HorizontalAlignment; } set { SetValue(ref _HorizontalAlignment, value); } }
        private AdaptiveHorizontalAlignment _HorizontalAlignment;

        /// <summary>
        ///     Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool Wrap { get { return _Wrap; } set { SetValue(ref _Wrap, value); } }
        private bool _Wrap;

        /// <summary>
        ///     When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public int MaxLines { get { return _MaxLines; } set { SetValue(ref _MaxLines, value); } }
        private int _MaxLines;

        public bool ShouldSerializeSize()
        {
            return Size != AdaptiveTextSize.Default;
        }

        public bool ShouldSerializeColor()
        {
            return Color != AdaptiveTextColor.Default;
        }

        public bool ShouldSerializeHorizontalAlignment()
        {
            return HorizontalAlignment != AdaptiveHorizontalAlignment.Left;
        }

        public bool ShouldSerializeWeight()
        {
            return Weight != AdaptiveTextWeight.Default;
        }

        public bool ShouldSerializeWrap()
        {
            return Wrap;
        }

        public bool ShouldSerializeIsSubtle()
        {
            return IsSubtle;
        }

        public bool ShouldSerializeMaxLines()
        {
            return MaxLines > 0;
        }
    }
}