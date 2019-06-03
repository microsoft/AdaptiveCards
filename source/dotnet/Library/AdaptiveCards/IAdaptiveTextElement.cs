// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    public interface IAdaptiveTextElement
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
        ///     Make the text italic
        /// </summary>
        bool Italic { get; set; }

        /// <summary>
        ///     Make the struck through
        /// </summary>
        bool Strikethrough { get; set; }

        /// <summary>
        ///     The text to display
        /// </summary>
        string Text { get; set; }

        /// <summary>
        ///     The font style of the TextBlock
        /// </summary>
        AdaptiveFontType FontType { get; set; }
    }
}
