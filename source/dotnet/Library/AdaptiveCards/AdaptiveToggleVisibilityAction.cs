using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Submit action gathers up input fields, merges with optional data field and generates event to client asking for
    ///     data to be submitted. It is up to the client to determine how that data is processed. For example: With
    ///     BotFramework bots the client would send an activity through the messaging medium to the bot.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveToggleVisibilityAction.TypeName)]
#endif
    public class AdaptiveToggleVisibilityAction : AdaptiveAction
    {
        public const string TypeName = "Action.ToggleVisibility";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     initial data that input fields will be combined with. This is essentially 'hidden' properties, Example:
        ///     {"id":"123123123"}
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [JsonConverter(typeof(ToggleElementsConverter))]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public List<object> TargetElements { get; set; } = new List<object>();
    }
}
