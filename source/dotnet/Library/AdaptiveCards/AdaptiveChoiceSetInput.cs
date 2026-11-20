// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Xml.Serialization;
using AdaptiveCards.Rendering;
using System.Text.Json.Serialization;


namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Input.ChoiceSet element.
    /// </summary>
    [XmlType(TypeName = AdaptiveChoiceSetInput.TypeName)]
    public class AdaptiveChoiceSetInput : AdaptiveInput
    {
        /// <summary>
        /// The AdaptiveCard element that this class implements.
        /// </summary>
        public const string TypeName = "Input.ChoiceSet";

        /// <inheritdoc/>
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Comma separated string of selected Choice values.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Value { get; set; }

        /// <summary>
        /// The style to use when displaying this Input.ChoiceSet.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveChoiceInputStyle), "compact")]
        public AdaptiveChoiceInputStyle Style { get; set; }

        /// <summary>
        /// Determines whether multiple selections are allowed.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool IsMultiSelect { get; set; }

        /// <summary>
        /// A collection of available choices.
        /// </summary>
        [JsonRequired]
        public List<AdaptiveChoice> Choices { get; set; } = new List<AdaptiveChoice>();

        /// <summary>
        /// Controls text wrapping behavior.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool Wrap { get; set; }

        /// <summary>
        /// Text to display as a placeholder.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Placeholder { get; set; }

        /// <summary>
        /// A dataQuery 
        /// </summary>
        [JsonPropertyName("choices.data")]
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlElement(typeof(AdaptiveDataQuery), ElementName = "Data.Query")]
        [DefaultValue(null)]
        public AdaptiveDataQuery DataQuery { get; set; }

        /// <inheritdoc />
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
