using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base of Action types
    /// </summary>
    public class ActionBase : TypedElement
    {
        /// <summary>
        ///     Title of the action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Title { get; set; }

        /// <summary>
        ///     Speak phrase for this action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlElement]
#endif
        public string Speak { get; set; }
    }
}