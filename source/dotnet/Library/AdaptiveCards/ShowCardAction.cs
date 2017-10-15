using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.
    /// </summary>
    public class ShowCardAction : ActionBase
    {
        public const string TypeName = "Action.ShowCard";

        public ShowCardAction()
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