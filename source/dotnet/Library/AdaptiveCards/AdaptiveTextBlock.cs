using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive
    ///     Cards.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveTextBlock.TypeName)]
#endif
    public class AdaptiveTextBlock : AdaptiveElement, ITextElement
    {
        public const string TypeName = "TextBlock";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
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
        public AdaptiveTextSize Size { get; set; }

        /// <summary>
        ///     The weight of the text
        /// </summary>
        public AdaptiveTextWeight Weight { get; set; }

        /// <summary>
        ///     The color of the text
        /// </summary>
        public AdaptiveTextColor Color { get; set; }

        /// <summary>
        ///     Make the text less prominent
        /// </summary>
        public bool IsSubtle { get; set; }

        /// <summary>
        ///     The text to display
        /// </summary>
        public string Text { get; set; } = " ";

        /// <summary>
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Wrap { get; set; }

        /// <summary>
        ///     When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public int MaxLines { get; set; }

        /// <summary>
        ///   The maximum width of the textblock
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public int MaxWidth { get; set; }

        /// <summary>
        ///     The font style of the TextBlock
        /// </summary>
        public AdaptiveFontStyle FontStyle { get; set; }
    }
}
