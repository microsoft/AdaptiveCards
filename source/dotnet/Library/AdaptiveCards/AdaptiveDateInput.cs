using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects date from the user
    /// </summary>
    public class AdaptiveDateInput : AdaptiveInput
    {
        public const string TypeName = "Input.Date";

        public override string Type => TypeName;

        /// <summary>
        ///     Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Placeholder { get { return _Placeholder; } set { SetValue(ref _Placeholder, value); } }
        private string _Placeholder;

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get { return _Value; } set { SetValue(ref _Value, value); } }
        private string _Value;

        /// <summary>
        ///     hint of minimum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Min { get { return _Min; } set { SetValue(ref _Min, value); } }
        private string _Min;

        /// <summary>
        ///     hint of maximum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Max { get { return _Max; } set { SetValue(ref _Max, value); } }
        private string _Max;

    }
}