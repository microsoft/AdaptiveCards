using System;

using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Represents one "fact" in a FactSet element.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveFact : ObservableObject
    {
        public AdaptiveFact(string title, string value)
        {
            Title = title;
            Value = value;
        }

        /// <summary>
        ///     The facts label
        /// </summary>
        [JsonRequired]
        public string Title { get { return _Title; } set { SetValue(ref _Title, value); } }
        private string _Title;

        /// <summary>
        ///     The fact's value
        /// </summary>
        [JsonRequired]
        public string Value { get { return _Value; } set { SetValue(ref _Value, value); } }
        private string _Value;

        /// <summary>
        ///     (Optional) Specifies what should be spoken for this entire element. This is simple text or SSML fragment
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("FactSet.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get { return _Speak; } set { SetValue(ref _Speak, value); } }
        private string _Speak;

    }
}