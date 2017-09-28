using Newtonsoft.Json;
using System;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base of Action types
    /// </summary>
    public abstract class AdaptiveActionBase : TypedElement
    {
        /// <summary>
        ///     Title of the action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string Title { get; set; }

        /// <summary>
        ///     Speak phrase for this action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlElement]
#endif
        [Obsolete("ActionBase.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }
    }

    [Obsolete("Use AdaptiveActionBase instead")]
    public abstract class ActionBase : AdaptiveActionBase { }
}