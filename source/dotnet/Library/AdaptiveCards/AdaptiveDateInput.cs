using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects date from the user
    /// </summary>
    public class AdaptiveDateInput : AdaptiveInput
    {
        public const string TypeName = "Input.Date";

        public override string Type { get; set; } = TypeName;

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
        ///     hint of minimum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Min { get; set; }

        /// <summary>
        ///     hint of maximum value(may be ignored by some clients)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Max { get; set; }

        public override string GetNonInteractiveValue()
        {
            return Value ?? $"*[{Placeholder}]*";
        }
    }
}