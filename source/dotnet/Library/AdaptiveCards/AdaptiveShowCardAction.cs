using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.
    /// </summary>
    [XmlType(TypeName = AdaptiveShowCardAction.TypeName)]
    public class AdaptiveShowCardAction : AdaptiveAction
    {
        public const string TypeName = "Action.ShowCard";

        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Container card to show when the action is invoked
        /// </summary>
        [JsonProperty(Required = Required.Always)]
        [XmlElement(typeof(AdaptiveCard), ElementName = AdaptiveCard.TypeName)]
        public AdaptiveCard Card { get; set; }
    }
}