using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Choice as part of a Input.AdaptiveChoiceSetInput element
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveChoice
    {
        /// <summary>
        ///     Display text for the choice
        /// </summary>
        [JsonRequired]
        public string Title { get; set; }

        /// <summary>
        ///     Internal value which will be collected as input if the choice is selected
        /// </summary>
        [JsonRequired]
        public string Value { get; set; }

        /// <summary>
        ///     Is this choice selected?
        /// </summary>
        [Obsolete("Choice.IsSelected has been deprecated.  Use AdaptiveChoiceSetInput.Value", false)]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool IsSelected { get; set; } = false;

        /// <summary>
        ///     (OPTIONAL) Speech description of the choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("AdaptiveChoiceSetInput.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }
    }
}