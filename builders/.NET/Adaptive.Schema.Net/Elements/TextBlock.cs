using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.
    /// </summary>
    public class TextBlock : CardElement
    {
        public TextBlock() 
        {

        }

        /// <summary>
        /// The size of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextSize? Size { get; set; }

        /// <summary>
        /// The weight of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextWeight? Weight { get; set; }

        /// <summary>
        /// The color of the text
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public TextColor? Color { get; set; }

        /// <summary>
        /// Should it be subtle?
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? IsSubtle { get; set; }


        /// <summary>
        /// The text to display
        /// </summary>
        [JsonRequired]
        public string Text { get; set; }

        /// <summary>
        /// Horizontal alignment for element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public HorizontalAlignment? HorizontalAlignment { get; set; }

        /// <summary>
        /// Is it allowed for the text to wrap
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool? Wrap { get; set; }

        /// <summary>
        /// When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public int? MaxLines { get; set; }
    }
}
