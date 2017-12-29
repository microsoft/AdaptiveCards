using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects text from the user
    /// </summary>
    public class AdaptiveTextInput : AdaptiveInput
    {
        public const string TypeName = "Input.Text";

        public override string Type => TypeName;

        /// <summary>
        ///     Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Placeholder { get { return _Placeholder; } set { SetPropertyValue(ref _Placeholder, value); } }
        private string _Placeholder;

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get { return _Value; } set { SetPropertyValue(ref _Value, value); } }
        private string _Value;

        /// <summary>
        ///     Hint of style of input, if client doesn't support the style it will become simple text input
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveTextInputStyle Style { get { return _Style; } set { SetPropertyValue(ref _Style, value); } }
        private AdaptiveTextInputStyle _Style;

        /// <summary>
        ///     true to collect multiple lines of text(default is false)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool IsMultiline { get { return _IsMultiline; } set { SetPropertyValue(ref _IsMultiline, value); } }
        private bool _IsMultiline;

        /// <summary>
        ///     hint of maximum length characters to collect(may be ignored by some clients)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public int MaxLength { get { return _MaxLength; } set { SetPropertyValue(ref _MaxLength, value); } }
        private int _MaxLength;

    }
}