using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.
    /// </summary>
    public class ActionShowCard : ActionBase
    {
        public ActionShowCard()
        {
            Type = "Action.ShowCard";
        }

        /// <summary>
        ///     Container card to show when the action is invoked
        /// </summary>
        [JsonRequired]
        public Container Card { get; set; }
    }
}