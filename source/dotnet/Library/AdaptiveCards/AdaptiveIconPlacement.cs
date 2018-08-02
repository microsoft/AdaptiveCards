using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Specifies the location of Icons on Actions
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveAction>), true)]
    public enum AdaptiveIconPlacement
    {
        /// <summary>
        /// Places the icons about the text in actions
        /// </summary>
        AboveTitle = 0,

        /// <summary>
        /// Place the icon to the left of the text in actions
        /// </summary>
        LeftOfTitle
    }
}
