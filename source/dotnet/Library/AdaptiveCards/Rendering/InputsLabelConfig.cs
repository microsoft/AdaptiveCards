// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Properties which control rendering of media
    /// </summary>
    public class InputLabelConfig
    {
        /// <summary>
        ///  The text color of the label
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextColor Color { get; set; } = AdaptiveTextColor.Default;

        /// <summary>
        ///  Make the label less prominent
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public bool IsSubtle { get; set; } = false;

        /// <summary>
        ///  The text size of the label
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextSize Size { get; set; } = AdaptiveTextSize.Default;

        /// <summary>
        ///  Suffix to be displayed next to the label. Only respected for required inputs
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public string Suffix { get; set; } = " *";

        /// <summary>
        ///  The text weight of the label
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        public AdaptiveTextWeight Weight { get; set; } = AdaptiveTextWeight.Default;
    }
}
