using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.
    /// </summary>
    public class AdaptiveShowCardAction : AdaptiveActionBase
    {
        public const string TypeName = "Action.ShowCard";

        public AdaptiveShowCardAction()
        {
            Type = TypeName;
        }

        /// <summary>
        ///     Container card to show when the action is invoked
        /// </summary>
        [JsonRequired]
        public AdaptiveCard Card { get; set; }
    }
}