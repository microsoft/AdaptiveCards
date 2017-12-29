using Newtonsoft.Json;
using System;
using System.Reflection;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base of Action types
    /// </summary>
    public abstract class AdaptiveAction : AdaptiveTypedElement
    {
        /// <summary>
        ///     Title of the action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Title { get { return _Title; } set { SetValue(ref _Title, value); } }
        private string _Title;

        // TODO: Title should be required is NOT a selectAction

        /// <summary>
        ///     Speak phrase for this action
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("ActionBase.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get { return _Speak; } set { SetValue(ref _Speak, value); } }
        private string _Speak;
    }

}