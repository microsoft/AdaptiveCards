using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    public interface ITextElement
    {
        /// <summary>
        ///     The size of the text
        /// </summary>
        AdaptiveTextSize Size { get; set; }

        /// <summary>
        ///     The weight of the text
        /// </summary>
        AdaptiveTextWeight Weight { get; set; }

        /// <summary>
        ///     The color of the text
        /// </summary>
        AdaptiveTextColor Color { get; set; }

        /// <summary>
        ///     Make the text less prominent
        /// </summary>
        bool IsSubtle { get; set; }

        /// <summary>
        ///     The text to display
        /// </summary>
        string Text { get; set; }

        /// <summary>
        ///     The font style of the TextBlock
        /// </summary>
        AdaptiveFontStyle FontStyle { get; set; }
    }
}
