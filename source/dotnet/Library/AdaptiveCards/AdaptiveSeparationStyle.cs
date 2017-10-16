using System;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the emphasize of an element to the previous element
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveSeparationStyle>), true)]
    [Obsolete("Use Spacing and Separator instead")]
    public enum AdaptiveSeparationStyle
    {
        /// <summary>
        ///     Default element spacing is applied from style
        /// </summary>
        Default,

        /// <summary>
        ///     No spacing is applied between elements
        /// </summary>
        None,

        /// <summary>
        ///     Strongly separate the element from the previous element
        /// </summary>
        Strong
    }
}