using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects a choice between two options from the user
    /// </summary>
    public class AdaptiveToggleInput : AdaptiveInput
    {
        public const string TypeName = "Input.Toggle";

        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Title text for toggle
        /// </summary>
        [JsonRequired]
        public string Title { get; set; }

        /// <summary>
        ///     Value to use for on (Default: true)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string ValueOn { get; set; } = bool.TrueString;

        /// <summary>
        ///     Value to use for off (Default: false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string ValueOff { get; set; } = bool.FalseString;

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get; set; }

        public override string GetNonInteractiveValue()
        {
            var x = Value == ValueOn ? "X" : " ";
            return $"[{x}] {Title}";
        }
    }
}