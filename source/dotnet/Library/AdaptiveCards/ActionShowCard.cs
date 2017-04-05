using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.
    /// </summary>
    public class ActionShowCard : ActionBase
    {
        public const string TYPE = "Action.ShowCard";

        public ActionShowCard()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Container card to show when the action is invoked
        /// </summary>
        [JsonRequired]
        public Container Card { get; set; }
    }
}