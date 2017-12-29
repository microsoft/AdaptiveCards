using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects a choice between two options from the user
    /// </summary>
    public class AdaptiveToggleInput : AdaptiveInput
    {
        public const string TypeName = "Input.Toggle";

        public override string Type => TypeName;

        /// <summary>
        ///     Title text for toggle
        /// </summary>
        [JsonRequired]
        public string Title { get { return _Title; } set { SetValue(ref _Title, value); } }
        private string _Title;

        /// <summary>
        ///     Value to use for on (Default: true)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string ValueOn { get { return _ValueOn; } set { SetValue(ref _ValueOn, value); } }
        private string _ValueOn = bool.TrueString;

        /// <summary>
        ///     Value to use for off (Default: false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string ValueOff { get { return _ValueOff; } set { SetValue(ref _ValueOff, value); } }
        private string _ValueOff = bool.FalseString;

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get { return _Value; } set { SetValue(ref _Value, value); } }
        private string _Value;

    }
}