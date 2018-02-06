using System.Collections.Generic;
using System.Linq;
using AdaptiveCards.Rendering;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     Element which collects choice from the user
    /// </summary>
    public class AdaptiveChoiceSetInput : AdaptiveInput
    {
        public const string TypeName = "Input.ChoiceSet";

        public override string Type { get; set; } = TypeName;

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

        public override string GetNonInteractiveValue()
        {
            var chosen = Value?.Split(',').Select(p => p.Trim()).Where(s => !string.IsNullOrEmpty(s)).ToList() ?? new List<string>();

            string choiceText;

            var choices = Choices.Select(choice => choice.Title).ToList();
            if (Style == AdaptiveChoiceInputStyle.Compact)
            {
                choiceText = IsMultiSelect 
                    ? $"Choices: {RendererUtilities.JoinString(choices, ", ", " and ")}" 
                    : $"Choices: {RendererUtilities.JoinString(choices, ", ", " or ")}";
            }
            else // if (adaptiveChoiceSetInput.Style == ChoiceInputStyle.Expanded)
            {
                choiceText = $"* {RendererUtilities.JoinString(choices, "\n* ", "\n* ")}";
            }

            RendererUtilities.JoinString(Choices.Where(c => chosen.Contains(c.Value)).Select(c => c.Title).ToList(), ", ", " and ");
            return choiceText;
        }
    }
}