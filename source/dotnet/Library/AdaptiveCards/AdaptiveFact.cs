using System;

using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Represents one "fact" in a FactSet element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveFact
    {
        public AdaptiveFact()
        {
        }

        public AdaptiveFact(string title, string value, string speak = null)
        {
            Title = title;
            Value = value;
#pragma warning disable CS0618 // Type or member is obsolete
            Speak = speak;
#pragma warning restore CS0618 // Type or member is obsolete
        }

        /// <summary>
        ///     The facts label
        /// </summary>
        [JsonRequired]
        public string Title { get; set; }

        /// <summary>
        ///     The fact's value
        /// </summary>
        [JsonRequired]
        public string Value { get; set; }

        /// <summary>
        ///     (Optional) Specifies what should be spoken for this entire element. This is simple text or SSML fragment
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("FactSet.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }
    }
}