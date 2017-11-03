using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input is used as part of a Form CardElement to collect information from a user
    /// </summary>
    public abstract class AdaptiveInput : AdaptiveElement
    {
        /// <summary>
        ///     Id for the value (will be used to identify collected input when SUBMIT is clicked)
        /// </summary>
        [JsonRequired]
        public new string Id { get; set; }

        /// <summary>
        ///     The input must have a value for it to be part of a Submit or Http action
        /// </summary>
        public bool IsRequired { get; set; }

        public bool ShouldSerializeIsRequired()
        {
            return IsRequired;
        }
    }
}