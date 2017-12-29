using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Input which collects number from the user
    /// </summary>
    public class AdaptiveNumberInput : AdaptiveInput
    {
        public const string TypeName = "Input.Number";

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
        public double Value { get { return _Value; } set { SetValue(ref _Value, value); } }
        private double _Value = double.NaN;

        /// <summary>
        ///     hint of minimum value(may be ignored by some clients)
        /// </summary>
        public double Min { get { return _Min; } set { SetValue(ref _Min, value); } }
        private double _Min = double.NaN;

        /// <summary>
        ///     hint of maximum value(may be ignored by some clients)
        /// </summary>
        public double Max { get { return _Max; } set { SetValue(ref _Max, value); } }
        private double _Max = double.NaN;

    }
}