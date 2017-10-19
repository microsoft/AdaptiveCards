using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects text from the user
    /// </summary>
    public class AdaptiveTextInput : AdaptiveInput
    {
        public const string TypeName = "Input.Text";

        public AdaptiveTextInput()
        {
            Type = TypeName;
        }

        /// <summary>
        ///     Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Placeholder { get; set; }

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get; set; }

        /// <summary>
        ///     Hint of style of input, if client doesn't support the style it will become simple text input
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveTextInputStyle Style { get; set; }

        /// <summary>
        ///     true to collect multiple lines of text(default is false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool IsMultiline { get; set; }

        /// <summary>
        ///     hint of maximum length characters to collect(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public int MaxLength { get; set; }

        public bool ShouldSerializeIsMultiline()
        {
            return IsMultiline;
        }
    }
}