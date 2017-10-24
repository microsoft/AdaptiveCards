using Newtonsoft.Json;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base of Action types
    /// </summary>
    public abstract class AdaptiveActionBase : AdaptiveTypedElement
    {
        /// <summary>
        ///     Title of the action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Title { get; set; }

        /// <summary>
        ///     Speak phrase for this action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("ActionBase.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }
    }
}