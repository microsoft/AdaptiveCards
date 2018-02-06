using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.
    /// </summary>
    public class AdaptiveShowCardAction : AdaptiveAction
    {
        public const string TypeName = "Action.ShowCard";

        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Container card to show when the action is invoked
        /// </summary>
        [JsonProperty(Required = Required.Always)]
        public AdaptiveCard Card { get; set; }
    }
}