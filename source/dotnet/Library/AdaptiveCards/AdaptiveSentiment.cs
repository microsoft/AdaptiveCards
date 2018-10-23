using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the action sentiment.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveSentiment>), true)]
    public enum AdaptiveSentiment
    {
        /// <summary>
        ///     The button is rendered as normal
        /// </summary>
        Default,

        /// <summary>
        ///     Positive sentiment
        /// </summary>
        Positive,

        /// <summary>
        ///     Destructive sentiment
        /// </summary>
        Destructive
    }
}
