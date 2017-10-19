using System.Collections.Generic;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Element which collects choice from the user
    /// </summary>
    public class AdaptiveChoiceSetInput : AdaptiveInput
    {
        public const string TypeName = "Input.ChoiceSet";

        public AdaptiveChoiceSetInput()
        {
            Type = TypeName;
        }

        /// <summary>
        ///      Comma separated string of selected Choice values
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get; set; }

        /// <summary>
        ///     Style for choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveChoiceInputStyle Style { get; set; }

        /// <summary>
        ///     allow multiple choices to be selected (default false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool IsMultiSelect { get; set; }

        /// <summary>
        ///     the choice options
        /// </summary>
        [JsonRequired]
        public List<AdaptiveChoice> Choices { get; set; } = new List<AdaptiveChoice>();


        public bool ShouldSerializeIsMultiSelect()
        {
            return IsMultiSelect;
        }
    }
}