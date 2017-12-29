using System.Collections.Generic;
using System.Collections.ObjectModel;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Element which collects choice from the user
    /// </summary>
    public class AdaptiveChoiceSetInput : AdaptiveInput
    {
        public const string TypeName = "Input.ChoiceSet";

        public override string Type => TypeName;

        /// <summary>
        ///      Comma separated string of selected Choice values
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Value { get { return _Value; } set { SetPropertyValue(ref _Value, value); } }
        private string _Value;

        /// <summary>
        ///     Style for choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveChoiceInputStyle Style { get { return _Style; } set { SetPropertyValue(ref _Style, value); } }
        private AdaptiveChoiceInputStyle _Style;

        /// <summary>
        ///     allow multiple choices to be selected (default false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public bool IsMultiSelect { get { return _IsMultiSelect; } set { SetPropertyValue(ref _IsMultiSelect, value); } }
        private bool _IsMultiSelect;

        /// <summary>
        ///     the choice options
        /// </summary>
        [JsonRequired]
        public ObservableCollection<AdaptiveChoice> Choices { get { return _Choices; } set { SetPropertyValue(ref _Choices, value); } }
        private ObservableCollection<AdaptiveChoice> _Choices = new ObservableCollection<AdaptiveChoice>();
    }
}