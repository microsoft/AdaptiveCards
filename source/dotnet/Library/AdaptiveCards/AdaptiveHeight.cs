using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the vertical size (height) of element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveHeight>), true)]
    public enum AdaptiveHeight
    {
        /// <summary>
        ///     The height of the element is wraps the element content
        /// </summary>
        Auto,

        /// <summary>
        ///     The height of the element uses as much space as it is able to
        /// </summary>
        Stretch
    }
}
