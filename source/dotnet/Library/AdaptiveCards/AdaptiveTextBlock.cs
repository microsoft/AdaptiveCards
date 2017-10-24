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

        public AdaptiveTextBlock()
        {
            Type = TypeName;
            Text = "";
        }

        /// <summary>
        ///     The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextSize Size { get; set; }

        /// <summary>
        ///     The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextWeight Weight { get; set; }

        /// <summary>
        ///     The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextColor Color { get; set; }

        /// <summary>
        ///     Should it be subtle?
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool IsSubtle { get; set; }

        /// <summary>
        ///     The text to display
        /// </summary>
        [JsonRequired]
        public string Text { get; set; }

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool Wrap { get; set; }

        /// <summary>
        ///     When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public int MaxLines { get; set; }

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