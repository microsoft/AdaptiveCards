// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of input labels
    /// </summary>
    public class LabelConfig
    {
        /// <summary>
        /// Required input label configs
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public InputLabelConfig RequiredInputs { get; set; } = new InputLabelConfig();

        /// <summary>
        /// Optional input label configs
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public InputLabelConfig OptionalInputs { get; set; } = new InputLabelConfig();

        /// <summary>
        /// Specifies the spacing between the label and the input
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveSpacing InputSpacing { get; set; }
    }
}
