using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace Adaptive
{
    /// <summary>
    /// The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.
    /// </summary>
    public partial class TextBlock : CardElement
    {
        public TextBlock() 
        {

        }

        /// <summary>
        /// The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public TextSize Size { get; set; }

        /// <summary>
        /// The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public TextWeight Weight { get; set; }

        /// <summary>
        /// The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public TextColor Color { get; set; }

        /// <summary>
        /// Should it be subtle?
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public bool IsSubtle { get; set; }

        /// <summary>
        /// The text to display
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Text { get; set; }

        /// <summary>
        /// Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public HorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        /// Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public bool Wrap { get; set; }

        /// <summary>
        /// When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public int MaxLines { get; set; }

        public bool ShouldSerializeSize() { return this.Size != TextSize.Normal; }
        public bool ShouldSerializeColor() { return this.Color != TextColor.Default; }
        public bool ShouldSerializeHorizontalAlignment() { return this.HorizontalAlignment != HorizontalAlignment.Left; }
        public bool ShouldSerializeWeight() { return this.Weight != TextWeight.Normal; }
        public bool ShouldSerializeWrap() { return this.Wrap; }
        public bool ShouldSerializeIsSubtle() { return this.IsSubtle; }
        public bool ShouldSerializeMaxLines() { return this.MaxLines > 0; }
    }
}
