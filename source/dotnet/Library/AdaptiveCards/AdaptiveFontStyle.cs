using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the font style of the TextBlock Elements
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveFontStyle>), true)]
    public enum AdaptiveFontStyle
    {
        /// <summary>
        ///     The default font style for general use
        /// </summary>
        Default,

        /// <summary>
        ///     An alternative font style for text
        /// </summary>
        Display,

        /// <summary>
        ///     The monospace font style
        /// </summary>
        Monospace
    }
}
