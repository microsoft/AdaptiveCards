using System.Globalization;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects number from the user
    /// </summary>
    public class AdaptiveNumberInput : AdaptiveInput
    {
        public const string TypeName = "Input.Number";

        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Placeholder text for the input desired
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Placeholder { get; set; }

        /// <summary>
        ///     The initial value for the field
        /// </summary>
        public double Value { get; set; } = double.NaN;

        /// <summary>
        ///     hint of minimum value(may be ignored by some clients)
        /// </summary>
        public double Min { get; set; } = double.NaN;

        /// <summary>
        ///     hint of maximum value(may be ignored by some clients)
        /// </summary>
        public double Max { get; set; } = double.NaN;

        public override string GetNonInteractiveValue()
        {
            return double.IsNaN(Value)
                ? Value.ToString(CultureInfo.InvariantCulture)
                : $"*[{Placeholder}]*";
        }
    }
}