using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Choice as part of a Input.AdaptiveChoiceSetInput element
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveChoice : ObservableObject
    {
        /// <summary>
        ///     Display text for the choice
        /// </summary>
        [JsonRequired]
        public string Title { get { return _Title; } set { SetValue(ref _Title, value); } }
        private string _Title;

        /// <summary>
        ///     Internal value which will be collected as input if the choice is selected
        /// </summary>
        [JsonRequired]
        public string Value { get { return _Value; } set { SetValue(ref _Value, value); } }
        private string _Value;

        /// <summary>
        ///     Is this choice selected?
        /// </summary>
        [Obsolete("Choice.IsSelected has been deprecated.  Use AdaptiveChoiceSetInput.Value", false)]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool IsSelected { get { return _IsSelected; } set { SetValue(ref _IsSelected, value); } }
        private bool _IsSelected = false;

        /// <summary>
        ///     (OPTIONAL) Speech description of the choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("AdaptiveChoiceSetInput.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get { return _Speak; } set { SetValue(ref _Speak, value); } }
        private string _Speak;
    }
}