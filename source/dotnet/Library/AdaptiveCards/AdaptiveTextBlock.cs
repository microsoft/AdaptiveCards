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

        public override string Type { get; set; } = TypeName;

        public AdaptiveTextBlock()
        {
            
        }

        public AdaptiveTextBlock(string text)
        {
            Text = text;
        }

        /// <summary>
        ///     The size of the text
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveTextSize Size { get; set; }

        /// <summary>
        ///     The weight of the text
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveTextWeight Weight { get; set; }

        /// <summary>
        ///     The color of the text
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveTextColor Color { get; set; }

        /// <summary>
        ///     Make the text less prominent
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool IsSubtle { get; set; }

        /// <summary>
        ///     The text to display
        /// </summary>
        [JsonRequired]
        public string Text { get; set; }

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool Wrap { get; set; }

        /// <summary>
        ///     When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public int MaxLines { get; set; }
    }
}